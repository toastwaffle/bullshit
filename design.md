# Bullshit Design

`bullshit` is vaguely modelled after `git`. The commit history is represented
using an object store and references for each branch.

  * `.bs/objects/<hash>` - content-addressed object store.
  * `.bs/branches/<branch>` - files containing the hash for each branch head.

## The object store

Objects in the object store can represent different types of object.

### Regular Files

Files are not delta-encoded in `bullshit`. A file will be represented as-is in
the object store. File metadata is not stored in the file object. Instead, it is
stored in the commit, which maps filenames to objects and metadata.

### Commits

Commit objects store various details:

  * References to parent commits.
  * A timestamp for when the commit was created.
  * A description.
  * A map from file paths to file contents and metadata.

The map of files is represented as a balanced binary tree with full file paths
as keys and file metadata as values. For efficiency, not all nodes of the tree
need to be defined in the same commit. Instead, nodes from ancestor commits may
be referenced directly. This bounds the size of the tree in each commit to
`O(m log n)`, where `n` is the total number of files in the repository and `m`
is the number of files modified in this commit.
