# Convenient Airports

- several connected components
     i) let's say all are trees, connecting trees will also result in a tree, and we
     have no choice rather than losing out one degree from each component, so the
     cost will be (number of merges * 2).

     ii) Let's say there are no repeated edges, but we have connected components of
     simple graphs,
     let's say two comp A and B,
     if A isn't a tree and B is, just merge costing 2
     if A and B aren't a tree, merge can cost 0, break one edge in each component,
     and join the corresponding four vertices.
