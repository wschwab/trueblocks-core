package statusPkg

/*-------------------------------------------------------------------------------------------
 * qblocks - fast, easily-accessible, fully-decentralized data from blockchains
 * copyright (c) 2016, 2021 TrueBlocks, LLC (http://trueblocks.io)
 *
 * This program is free software: you may redistribute it and/or modify it under the terms
 * of the GNU General Public License as published by the Free Software Foundation, either
 * version 3 of the License, or (at your option) any later version. This program is
 * distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even
 * the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details. You should have received a copy of the GNU General
 * Public License along with this program. If not, see http://www.gnu.org/licenses/.
 *-------------------------------------------------------------------------------------------*/

import (
	"strconv"

	"github.com/TrueBlocks/trueblocks-core/src/apps/chifra/cmd/root"
	"github.com/TrueBlocks/trueblocks-core/src/apps/chifra/pkg/output"
	"github.com/TrueBlocks/trueblocks-core/src/apps/chifra/pkg/validate"
	"github.com/spf13/cobra"
)

func Validate(cmd *cobra.Command, args []string) error {
	output.Format = Options.Globals.Format
	if Options.Depth > 3 {
		return validate.Usage("The {0} option ({1}) must {2}.", "--depth", strconv.FormatUint(Options.Depth, 10), "be less than four (4)")
	}

	err := validate.ValidateEnumSlice("--types", Options.Types, "[blocks|txs|traces|slurps|prices|all]")
	if err != nil {
		return err
	}

	err = validate.ValidateEnumSlice("--migrate", Options.Migrate, "[test|abi_cache|block_cache|tx_cache|trace_cache|recon_cache|name_cache|slurp_cache|all]")
	if err != nil {
		return err
	}

	err = validate.ValidateEnumSlice("modes", args, "[index|monitors|collections|names|abis|caches|some|all]")
	if err != nil {
		return err
	}

	Options.TestLog()

	return root.ValidateGlobals(&Options.Globals, args)
}