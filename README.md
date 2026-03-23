# MoldenPhaseSwap

Many computational chemistry software packages are able to output electronic structure data in the form of a Molden file.  In some instances, when performing QM-MD or QM/MM-MD, outputting the Molden file for each frame or timestep can result in the orbital signs being "flipped" from one to the next.  From a purely chemistry-related viewpoint this is not a problem, however when one wishes to use visualization software to show the alpha/beta spin of orbitals over time, these sign flips can result in a "flicker" where orbital colors may switch back and forth rapidly.  Not only is this visually jarring, it can also distract from the important scientific information being presented.

This program can take an arbitrary number of molden files as command line arguments (assuming the user is capable of providing in a time-sorted list) and iterates through each file, comparing each orbital between file-pairs, and identifying those orbitals which need to be phase-switched. The molden files are updated accordingly, and no other changes are made.

If you use Molden files to visualize molecular orbitals, this can help you keep everything visually consistent.
