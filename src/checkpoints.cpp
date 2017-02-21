// Copyright (c) 2009-2015 The Bitcoin developers
// Copyright (c) 2011-2015 Litecoin Developers
// Copyright (c) 2013-2015 Globalcoin Developers
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
        boost::assign::map_list_of //Gensis and Checkpoints
        (        0, uint256("0xa28dcb138cef4fa6ea6e1a49fafb352c72c4fffa6674f2bb7e506817e27bdfcc"))
        (     2230, uint256("0x71a9d486b349c840ffdf29927414aa903c1443f945b7b2618d807ea8f3e15699"))
        (     7000, uint256("0xf8aa8224404caeada717008f6df70db2a2b6d04e44c29ee1fa7abcee7ae2aa5a"))
        (    12000, uint256("0x0f44a3b36b9d501f59a4e6b218a1f311b5342de436b134148cd902be7c3b4b05"))
        (    85000, uint256("0x18d9c82e34157fb48f7722d1557bb505f7794e3465bbf0dbbde7b22b8dd98ebd"))
        (   185000, uint256("0x603af05e5e6964e5c2718658a4dbdc8f22d0826c266a3427468ae7bb7c129158"))
        (   240000, uint256("0x715e10e343468c2383197c7c5ce463cb71c816fa35e6433bfff2f48b72d80142"))
        (   260000, uint256("0x5f04c7584f6d93d3cb96a91c71b2003340e3fcb15d5be327ca70506acd8dff9d"))
        (   380000, uint256("0x1e4dca66760910b9b14b58c1daf7b012603b9d6208e23ef3af1a5a0900d5aec4"))
        (   480000, uint256("0x03f2e5815706d70d2dd88c25851086ad51173b7677f555b585d9abbdf65677c0"))
        (   500000, uint256("0xff93802621e2e90824c73ec6d672406a1beaee9610582cd28613e4abc0c1e855"))
        (   580000, uint256("0x57eb0935278e79883a5523b2a2a8d72a16430494a0e60b20dea40068a62ed846"))
        (   600000, uint256("0xdfc25b486ee340967320ebb8439f6bc238ee3e90781515bc21e1588b50d54eb4"))
        (   660000, uint256("0x6ae70c28f3b942d9c0b6ce1d44c98f58e61aa8e4ace0573718cf9faed33438e0"))
        (   800000, uint256("0xe907d0d8963409581d65507434c90c3ce3719f058a1865282e28fc492e42c3dc"))
        (   900000, uint256("0xa5e3ed21f3e14764987f2ac9445c7ab0a601fd56cfe62187ece99e685ebf124e"))
        (  1000000, uint256("0xfea5852b22a9f82d9f90b3a1430b43926292b124b7ed5fb10de1353594f8e572"))
        (  1193100, uint256("0x124c12e426c1acf0c868fccec009bff2dc84ca91cff77cc599b91505fa4bdccd"))
        (  2514000, uint256("0x4801f67144302813256009faf6bb888c66f93ee386d12bb78fb60ef688c1491c"))
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
