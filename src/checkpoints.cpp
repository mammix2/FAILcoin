// Copyright (c) 2009-2012 The Bitcoin developers
// Copyright (c) 2011-2012 Litecoin Developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <boost/assign/list_of.hpp> // for 'map_list_of()'
#include <boost/foreach.hpp>

#include "checkpoints.h"

#include "main.h"
#include "uint256.h"

namespace Checkpoints
{
    typedef std::map<int, uint256> MapCheckpoints;

    //
    // What makes a good checkpoint block?
    // + Is surrounded by blocks with reasonable timestamps
    //   (no blocks before with a timestamp after, none after with
    //    timestamp before)
    // + Contains no strange transactions
    //
    static MapCheckpoints mapCheckpoints =
        boost::assign::map_list_of // Yo dawg, this is the secret. Checkpoint 0 hash == Genesis block hash.
        (         0, uint256("0xd3221b0aeff5ac74ece3fea2f91572dfc4d214521d9cca435ab06a5d9e364022"))
        (         10, uint256("0x8547d0ad0c2803f3a9ca2ff9ab4989bb47501af3fa5bdfa826d8091278a31ce4"))
        (         500, uint256("0x3be983a2240ddd0af241a78d965f0bbb8b5c57c550ef8eaaf990bf2d9880280e"))
        (         10000, uint256("0x689eae5befa3143f16f7c877061e389e28c94da4284d4b1509bfca10a198f4bf"))
        (         20000, uint256("0xc869f51f46721be11d9d1a3a72d4469f1d9e592f815e4e3844a334594bd7bc60"))
        (         30000, uint256("0x2e5975d55366cb20608fbe44b450dea78a7e1c419c72f828f4973ed911fc53c8"))
        (         50000, uint256("0xdb9139f011c9250a099da7467b6563b174a20643c59792db487d381fcbd31a83"))
        ;

    bool CheckBlock(int nHeight, const uint256& hash)
    {
        if (fTestNet) return true; // Testnet has no checkpoints

        MapCheckpoints::const_iterator i = mapCheckpoints.find(nHeight);
        if (i == mapCheckpoints.end()) return true;
        return hash == i->second;
    }

    int GetTotalBlocksEstimate()
    {
        if (fTestNet) return 0;
        return mapCheckpoints.rbegin()->first;
    }

    CBlockIndex* GetLastCheckpoint(const std::map<uint256, CBlockIndex*>& mapBlockIndex)
    {
        if (fTestNet) return NULL;

        BOOST_REVERSE_FOREACH(const MapCheckpoints::value_type& i, mapCheckpoints)
        {
            const uint256& hash = i.second;
            std::map<uint256, CBlockIndex*>::const_iterator t = mapBlockIndex.find(hash);
            if (t != mapBlockIndex.end())
                return t->second;
        }
        return NULL;
    }
}
