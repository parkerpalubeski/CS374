What could go wrong if we didn't lock the header?

If the header isn't locked, several processes might read the same values at once, before they are modified. For instance, one process might read offset the same as another, even if one of them were to add an n length string to the log (and thus, would require offset to increment by n). This problem could cause all kinds of unpredictable behavior, like overwriting, skipping over space, duplicates, etc.

What could go wrong if we didn't lock the record? 

If the record isn't locked, external processes might read a record while it's being written, which could cause all kinds of garbage values to print while dumping the log.