simple GossipNode
{
    parameters:
        @display("i=block/routing");
    gates:
        input in[];
        output out[];
}

network meshnetwork
{
    types:
        channel Channel extends ned.DelayChannel
        {
            delay = 100ms;
        }

    submodules:
        node[16]: GossipNode {
        }
    connections allowunconnected:

        // === Circle A (nodes 0-3) ===
        node[0].out++ --> Channel --> node[1].in++;
        node[0].out++ --> Channel --> node[2].in++;
        node[0].out++ --> Channel --> node[3].in++;

        node[1].out++ --> Channel --> node[0].in++;
        node[1].out++ --> Channel --> node[2].in++;
        node[1].out++ --> Channel --> node[3].in++;

        node[2].out++ --> Channel --> node[0].in++;
        node[2].out++ --> Channel --> node[1].in++;
        node[2].out++ --> Channel --> node[3].in++;

        node[3].out++ --> Channel --> node[0].in++;
        node[3].out++ --> Channel --> node[1].in++;
        node[3].out++ --> Channel --> node[2].in++;

        // === Circle B (nodes 4-7) ===
        node[4].out++ --> Channel --> node[5].in++;
        node[4].out++ --> Channel --> node[6].in++;
        node[4].out++ --> Channel --> node[7].in++;

        node[5].out++ --> Channel --> node[4].in++;
        node[5].out++ --> Channel --> node[6].in++;
        node[5].out++ --> Channel --> node[7].in++;

        node[6].out++ --> Channel --> node[4].in++;
        node[6].out++ --> Channel --> node[5].in++;
        node[6].out++ --> Channel --> node[7].in++;

        node[7].out++ --> Channel --> node[4].in++;
        node[7].out++ --> Channel --> node[5].in++;
        node[7].out++ --> Channel --> node[6].in++;

        // === Circle C (nodes 8-11) ===
        node[8].out++ --> Channel --> node[9].in++;
        node[8].out++ --> Channel --> node[10].in++;
        node[8].out++ --> Channel --> node[11].in++;

        node[9].out++ --> Channel --> node[8].in++;
        node[9].out++ --> Channel --> node[10].in++;
        node[9].out++ --> Channel --> node[11].in++;

        node[10].out++ --> Channel --> node[8].in++;
        node[10].out++ --> Channel --> node[9].in++;
        node[10].out++ --> Channel --> node[11].in++;

        node[11].out++ --> Channel --> node[8].in++;
        node[11].out++ --> Channel --> node[9].in++;
        node[11].out++ --> Channel --> node[10].in++;

        // === Circle D (nodes 12-15) ===
        node[12].out++ --> Channel --> node[13].in++;
        node[12].out++ --> Channel --> node[14].in++;
        node[12].out++ --> Channel --> node[15].in++;

        node[13].out++ --> Channel --> node[12].in++;
        node[13].out++ --> Channel --> node[14].in++;
        node[13].out++ --> Channel --> node[15].in++;

        node[14].out++ --> Channel --> node[12].in++;
        node[14].out++ --> Channel --> node[13].in++;
        node[14].out++ --> Channel --> node[15].in++;

        node[15].out++ --> Channel --> node[12].in++;
        node[15].out++ --> Channel --> node[13].in++;
        node[15].out++ --> Channel --> node[14].in++;

        // === Inter-circle links between gateway 'a' nodes (0, 4, 8, 12) ===
        node[0].out++ --> Channel --> node[4].in++;
        node[4].out++ --> Channel --> node[8].in++;
        node[8].out++ --> Channel --> node[12].in++;
        node[12].out++ --> Channel --> node[0].in++;

        // Bidirectional (if needed)
        node[4].out++ --> Channel --> node[0].in++;
        node[8].out++ --> Channel --> node[4].in++;
        node[12].out++ --> Channel --> node[8].in++;
        node[0].out++ --> Channel --> node[12].in++;
}
