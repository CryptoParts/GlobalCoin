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
        boost::assign::map_list_of //Gensis and Checkpoints
        (         0, uint256("0xa28dcb138cef4fa6ea6e1a49fafb352c72c4fffa6674f2bb7e506817e27bdfcc"))
        (         2230, uint256("0x71a9d486b349c840ffdf29927414aa903c1443f945b7b2618d807ea8f3e15699"))
        (         7000, uint256("0xf8aa8224404caeada717008f6df70db2a2b6d04e44c29ee1fa7abcee7ae2aa5a"))
        (         12000, uint256("0x0f44a3b36b9d501f59a4e6b218a1f311b5342de436b134148cd902be7c3b4b05"))
        (         18000, uint256("0x21fb15db01439362a5113ea3c1cac04163673798974fd43f0c0e6532fab5f26d"))
        (         22300, uint256("0x063e89eae28119aa94cf44c9d7e155aec9ae4229dba37bd6456431e49868a039"))
        (         22644, uint256("0x9aec5d2cb0f43cc8089878daf85d5c441e9ee9b0e030263f13c23befef11a0cd"))
        (         26051, uint256("0x9541a7030ae49c99660ccf3242ccee6959153877fbfc1d53afe9cc9c04d85f6e"))
        (         39058, uint256("0x1ff3b6e143861c01fd952c16501c32b3723c8c14b8f1c62ca63d1daa22f5b0dd"))
        (         45053, uint256("0x403536342585bcfc3b299f919dff220c4a9facd2d4bb83f77aa8ab3ba3f0171c"))
        (         52062, uint256("0xccfe2de478a51a69cccd6ee765caee4f78d8ee4655ca708555b806aac911feca"))
        (         63390, uint256("0x9176fa0f727374ad7eda5206912cd81eefeb0a2ebb8878dab84f8cb1b65ee43f"))
        (         63399, uint256("0xae14b26cab4753cd6f0d15c3223ac7046f944d7510988851a48a6af5fd556b51"))
        (         63417, uint256("0xcc0a685b344f4fd1503974ef95d63f545edfe831fa30e1770cc676181d674fec"))
        (         63424, uint256("0x8ebe2f5acebe0bce1819645ceca3337c3c312ab8b2c298a5d5cf542531117a4b"))
        (         75000, uint256("0x2ace5643f4501d542bd6c047605c619c4854585050b677f97a6be7880eb02766"))
        (         85000, uint256("0x18d9c82e34157fb48f7722d1557bb505f7794e3465bbf0dbbde7b22b8dd98ebd"))
        (         90000, uint256("0xbd27920f0035a682e5807ed4539ee7e338538abca2915ce21b8e17725a161a7f"))
        (         97000, uint256("0x90c415d63cf43621a28e9962d31c07ffeea01184bbd1f5f7ffc71dc7cc33e1a8"))
        (         97200, uint256("0x5c561e62f3618555b8ace2345fd789fe2ba339da0882b28df46c372579eacf0b"))
        (         130000, uint256("0x695ca714ab42b13425b59dcc4c861bcb78070a8bfd47250b42cd87fb1b1c9981"))
        (         133000, uint256("0x16c8b8b8328c2236f221bdb1310fc73adc17367ec2c175af35ff2577d5a480d3"))
        (         179849, uint256("0xffd88e4420b67f8f92fe793e9dd19bba3a929747d491afe923a170d07a98299d"))
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
