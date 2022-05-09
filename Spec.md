Simple Hash Specification
=========================

- Key Input must be from a file with txt extension
- Expect good input to be space separated words with command letter at the fron of keys
  + **Iword** means insert word into table
  + **Dword** means delete word from table
- Should ignore bad inputs
- Keys are lowercase english words only (i.e. a-z)
- Length of key at most 10
- 'Hash function' is just taking final letter of key mapped a-z to 0-25 % 10
- Hash table contains exactly 26 slots (a-z)
- If there is no space print a warning
- Each table slot should have 3 different statuses: 'never used', 'tombstone', 'occupied'
- All slots start as 'never used'
- Searching works as follows:
  + Given key, calculate its hash
  + First try the corresponding table slot
  + If it's there, its found
  + If it's 'never used', it doesn't exist
  + If it's 'tombstone' or 'occupied', move to next slot
  + Continue until found or sure doesn't exist
- Insertion works as follows:
  + First perform search, if key exists do nothing
  + Use hash value to find a slot
  + If slot is not 'occupied', add key there
  + Otherwise, continue until free slot or no remaining possibilities
- Deletion works as follows:
  + Given a key, search for it
  + If not found, do nothing
  + If found, change to 'tombstone'
- Output the table after input is read as:
  + Slot [i]: Status (status): Data (data)