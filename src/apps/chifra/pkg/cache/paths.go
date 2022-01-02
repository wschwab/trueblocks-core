// Copyright 2021 The TrueBlocks Authors. All rights reserved.
// Use of this source code is governed by a license that can
// be found in the LICENSE file.

package cache

import (
	"path"
	"strings"

	"github.com/TrueBlocks/trueblocks-core/src/apps/chifra/pkg/config"
)

// CachePath helps to keep track of cache paths and extensions depending on
// chunk type
type CachePath struct {
	Type      CacheType
	RootPath  string
	Subdir    string
	Extension string
}

var cacheFolders = map[CacheType]string{
	BloomChunk:    "blooms/",
	IndexChunk:    "finalized/",
	BlockCache:    "blocks/",
	TxCache:       "txs/",
	TraceCache:    "traces/",
	MonitorCache:  "monitors/",
	NeighborCache: "neighbors/",
	ReconCache:    "recons/",
}

// New sets correct values of Subdir and Extension properties based on cacheType
func (cl *CachePath) New(cacheType CacheType) {
	indexPath := config.ReadTrueBlocks().Settings.IndexPath
	cachePath := config.ReadTrueBlocks().Settings.CachePath

	if cacheType == BloomChunk || cacheType == IndexChunk {
		cl.RootPath = indexPath
	} else {
		cl.RootPath = cachePath
	}

	cl.Extension = ".bin"
	if cacheType == BloomChunk {
		cl.Extension = ".bloom"
	}
	cl.Subdir = cacheFolders[cacheType]
}

// GetFullPath builds a full path from the CachePath type
func (cl *CachePath) GetFullPath(name string) string {
	switch cl.Type {
	case IndexChunk:
		fallthrough
	case BloomChunk:
		fallthrough
	case MonitorCache:
		return path.Join(cl.RootPath, cl.Subdir, name+cl.Extension)
	default:
		return path.Join(cl.RootPath, cl.Subdir)
	}
}

// RemoveExtension removes Extension (".bloom" or ".bin") from fileName
func (cl *CachePath) RemoveExtension(fileName string) string {
	return strings.Replace(fileName, cl.Extension, "", 1)
}

// String turns cachePath data (RootPath and Subdir) into a path
// and returns it as a string
func (cl *CachePath) String() string {
	return path.Join(cl.RootPath, cl.Subdir)
}