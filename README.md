# ClansTools

A small C++ command-line utility that bridges [BLAST](https://blast.ncbi.nlm.nih.gov/)
all-against-all comparisons, [CLANS](https://github.com/proteinevolution/clans)
cluster maps, and [RapidNJ](https://github.com/somme89/rapidNJ) neighbor-joining
tree building - three tools that don't otherwise speak the same file formats.

It supports two independent conversions:

1. **BLAST output -> CLANS file**: turns an all-against-all BLAST search's
   tabular e-values, plus the FASTA file of sequences that were searched,
   into a `.clans` file CLANS can load and cluster.
2. **Distance matrix for RapidNJ**: produces a distance matrix in relaxed
   PHYLIP format (sequence names may be longer than 10 characters), either
   directly from the same BLAST e-values, or from the 2D/3D positions
   CLANS computed after clustering (i.e. loading back a `.clans` file CLANS
   has already arranged).

## Building

Requires a C++ compiler (`g++` on Linux/macOS, `cl` on Windows) and `make`.

```sh
make
```

Produces the `ClansTools` binary in the repository root. `make clean`
removes build artifacts.

## Usage

```
ClansTools [OPTIONS]
```

| Option | Description |
| --- | --- |
| `-h`, `--help` | Display the help message and exit. Ignores all other options. |
| `-s`, `--sequence-file ARG` | The FASTA file of sequences that were BLASTed. Ignored if `--clans-file` is used. |
| `-i`, `--input-file ARG` | Tab-separated BLAST output: query ID, subject ID, e-value, one all-against-all hit per line. Ignored if `--clans-file` is used. |
| `-c`, `--clans-file ARG` | A `.clans` file to read cluster-map positions from instead of BLAST output. Also used to extract sequence names. When set, `--sequence-file`/`--input-file` are ignored. |
| `-d`, `--matrix-output-file ARG` | Write a distance matrix (relaxed PHYLIP format) to this path. |
| `-o`, `--clans-output-file ARG` | Write a `.clans` file to this path, built from `--sequence-file` and `--input-file`. |
| `-m`, `--make-half-matrix` | Write only the lower-triangular half of the matrix. Not usable with RapidNJ, which expects the full matrix. |
| `-u`, `--use-short-names` | Truncate sequence names at the first space, instead of the default of replacing spaces/colons/slashes with underscores and stripping semicolons, commas, quotes, brackets, and parentheses. |
| `-q`, `--square-distances` | Square the distances written to the matrix. |

At least one of `--matrix-output-file`/`--clans-output-file` is required.

### Convert BLAST output to a CLANS file

```sh
ClansTools -i blast_hits.tsv -s sequences.fasta -o clusters.clans
```

Load `clusters.clans` in CLANS to cluster and arrange the sequences.

### Convert BLAST output directly to a RapidNJ distance matrix

```sh
ClansTools -i blast_hits.tsv -s sequences.fasta -d distances.phy
```

### Convert a CLANS file's positions to a RapidNJ distance matrix

Once CLANS has arranged a cluster map (e.g. via the workflow above), turn
its 2D/3D positions into distances for tree building:

```sh
ClansTools -c clusters.clans -d distances.phy
rapidnj distances.phy -i pd -o t > tree.newick
```

## Third-party code

`src/getopt_pp/` bundles [GetOpt_pp](https://github.com/dgutson/getoptpp)
by Daniel Gutson, FuDePAN, licensed under the GNU General Public License
v3 - see [`LICENSE`](LICENSE), which also covers this project as a whole.

## License

GPLv3 - see [`LICENSE`](LICENSE).
