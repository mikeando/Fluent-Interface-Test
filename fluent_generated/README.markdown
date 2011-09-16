Shows how we could use python to generate the fluent interface from a simple config file at compile time.

The file `transition_table.py` contains the transitions the fluent interface can go through.
`helper.py` generates the source and header files from that file. (You can find them in the generated directory for reference).

The usage of the interface is in `fluent_simple.cpp`.
