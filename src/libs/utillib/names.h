#pragma once
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
#include "basetypes.h"
#include "conversions.h"

namespace qblocks {

//-----------------------------------------------------------------------
typedef bool (*NAMEFUNC)(CAccountName& name, void* data);
extern bool forEveryName(bool old, NAMEFUNC func, void* data);

//-----------------------------------------------------------------------
extern bool loadNames(bool old);
extern bool clearNames(bool old);
extern bool findName(bool old, const address_t& addr, CAccountName& acct);
extern bool findToken(bool old, const address_t& addr, CAccountName& acct);
extern void addPrefundToNamesMap(bool old, CAccountName& account, uint64_t cnt);
extern size_t nNames(bool old);
extern bool oldNames;

}  // namespace qblocks
