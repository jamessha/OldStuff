Initialization and launch in Program.cs

Uses Microsoft Speech recognizer for voice to text

Runs a graph and a trie side by side
- Graph used to find nodes with responses to a user input (or if none exists, self updates)
- Trie used to find actions to select phrases, used so that we don't move in the graph when commands are issued