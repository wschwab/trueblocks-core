// Copyright 2021 The TrueBlocks Authors. All rights reserved.
// Use of this source code is governed by a license that can
// be found in the LICENSE file.
/*
 * Parts of this file were generated with makeClass --run. Edit only those parts of
 * the code inside of 'EXISTING_CODE' tags.
 */

package receiptsPkg

// EXISTING_CODE
import (
	"context"
	"fmt"
	"net/http"
	"strings"

	"github.com/TrueBlocks/trueblocks-core/src/apps/chifra/pkg/output"
	"github.com/TrueBlocks/trueblocks-core/src/apps/chifra/pkg/rpcClient"
	"github.com/TrueBlocks/trueblocks-core/src/apps/chifra/pkg/types"
	"github.com/TrueBlocks/trueblocks-core/src/apps/chifra/pkg/utils"
	"github.com/spf13/cobra"
)

// EXISTING_CODE

// RunReceipts handles the receipts command for the command line. Returns error only as per cobra.
func RunReceipts(cmd *cobra.Command, args []string) (err error) {
	opts := receiptsFinishParse(args)
	// EXISTING_CODE
	// EXISTING_CODE
	err, _ = opts.ReceiptsInternal()
	return
}

// ServeReceipts handles the receipts command for the API. Returns error and a bool if handled
func ServeReceipts(w http.ResponseWriter, r *http.Request) (err error, handled bool) {
	opts := receiptsFinishParseApi(w, r)
	// EXISTING_CODE
	// EXISTING_CODE
	return opts.ReceiptsInternal()
}

// ReceiptsInternal handles the internal workings of the receipts command.  Returns error and a bool if handled
func (opts *ReceiptsOptions) ReceiptsInternal() (err error, handled bool) {
	err = opts.validateReceipts()
	if err != nil {
		return err, true
	}

	// EXISTING_CODE
	if opts.Articulate {
		err = opts.Globals.PassItOn("getReceipts", opts.Globals.Chain, opts.toCmdLine(), opts.getEnvStr())
		return err, true
	}

	clientVersion, err := rpcClient.GetVersion(opts.Globals.Chain)
	if err != nil {
		return err, true
	}
	erigonUsed := utils.IsClientErigon(clientVersion)

	ctx, cancel := context.WithCancel(context.Background())

	// TODO(dszlachta): I renamed this function to `renderTransaction`. Render meaning "send out". We're not really getting as nothing is returned
	renderTransaction := func(models chan types.Modeler[types.RawReceipt], errors chan error) {
		// TODO: stream transaction identifiers
		for idIndex, rng := range opts.TransactionIds {
			txList, err := rng.ResolveTxs(opts.Globals.Chain)
			// TODO: rpcClient should return a custom type of error in this case
			if err != nil && strings.Contains(err.Error(), "not found") {
				errors <- err
				continue
			}
			if err != nil {
				errors <- err
				cancel()
				return
			}
			for _, tx := range txList {
				if tx.BlockNumber < uint32(byzantiumBlockNumber) && !erigonUsed {
					err = opts.Globals.PassItOn("getReceipts", opts.Globals.Chain, getReceiptsCmdLine(opts, []string{rng.Orig}), opts.getEnvStr())
					if err != nil {
						errors <- err
						cancel()
						return
					}
					continue
				}

				receipt, err := rpcClient.GetTransactionReceipt(opts.Globals.Chain, uint64(tx.BlockNumber), uint64(tx.TransactionIndex))
				if err != nil && err.Error() == "not found" {
					errors <- fmt.Errorf("transaction %s not found", opts.Transactions[idIndex])
					continue
				}
				if err != nil {
					errors <- err
					cancel()
					return
				}

				models <- &receipt
			}
		}
	}

	// TODO(dszlachta): There's no reason for this processing to be in the calling code. Put this inside of StreamMany and remove it from the OutputOptions. It makes this code much cleaner.
	var meta *rpcClient.MetaData
	if opts.Globals.Format == "api" {
		meta, err = rpcClient.GetMetaData(opts.Globals.Chain, opts.Globals.TestMode)
		if err != nil {
			return err, true
		}
	}
	err = output.StreamMany(ctx, opts.Globals.Writer, renderTransaction, output.OutputOptions{
		ShowKeys:   !opts.Globals.NoHeader,
		ShowRaw:    opts.Globals.Raw,
		ShowHidden: opts.Globals.Verbose,
		Format:     opts.Globals.Format,
		JsonIndent: "  ",
		Meta:       meta,
	})

	handled = true
	// EXISTING_CODE

	return
}

// EXISTING_CODE
// TODO: create EXISTING CODE block at the beginning of this file to keep constants ther
var byzantiumBlockNumber = 4370000

// TODO: remove this function when rewrite to Go is completed. It is only used to send
// pre-Byzantium transactions to C++ version
func getReceiptsCmdLine(opts *ReceiptsOptions, txs []string) string {
	options := ""
	if opts.Articulate {
		options += " --articulate"
	}

	options += " " + strings.Join(txs, " ")
	return options
}

// EXISTING_CODE
