## 280DataStructure-Final
Final project for Data Structure. 

Taking the implementation side of things allows us to create fake documents or data to allow us to enter the algorithm. Then having a system to time, the different areas to see what can be implemented or what can be improved.

Main Idea - 
Supply Chain Management: An inventory system for a warehouse can be integrated into a larger supply chain management system using data structures such as graphs and trees to organize and track inventory movements between warehouses, manufacturers, and retailers.

Data structures being used.
-	Tree Structure: The supply chain management system can be represented as a tree structure, with the inventory system for the warehouse as one of the branches. The inventory system can be connected to the other branches of the tree, representing other components of the supply chain, such as suppliers, manufacturers, distributors, and retailers.
-	Queue: When items are received, they can be added to the back of the queue, and when they are shipped out, they can be removed from the front of the queue. This way, the queue always reflects the current state of inventory in the warehouse, with the oldest items at the front of the queue and the newest items at the back.
-	Instead of queuing we could use a hash table.
o	Using a hash table for inventory tracking can offer several advantages over other data structures. First, it provides constant-time lookup and retrieval of items, which is important for large warehouses with a high volume of inventory. Second, it allows for efficient storage and retrieval of data since items can be stored and accessed based on their unique identifiers rather than their physical location in the warehouse. Finally, it can help prevent errors and discrepancies in inventory tracking, since each item is uniquely identified and linked to its corresponding information in the hash table.
