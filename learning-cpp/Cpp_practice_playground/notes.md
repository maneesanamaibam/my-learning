
- simple binary tree  and its uses 
- complete binary tree and its uses 
- perfect binary tree and its uses 
- skewed binary tree and its uses
- Binary search tree and its uses












height of the left node - height of the right node <= 1 
height -> number of nodes attached to that node

This tree is height-balanced! How did we determine that? Let’s go through and break our thought process down into a series of steps to find out.

High-level algorithm to determine if a tree is height-balanced
Start from the leaf nodes and move towards the root.

Along with traversing the tree, compute heights of left-subtree and right-subtree of each node. The height of a leaf node is always 0.

At each node, check if the difference between the height of the left and right sub-tree is more than 1, if so, then it means that the tree is not balanced.

If you have completely traversed the tree and haven’t caught the above condition, then the tree is balanced.


Example
Implementing what we learned from the above four steps in the illustration below. Here, HLT means the height of the Left Tree and HRT means the height of the right tree: 

    1
  /  \
 2    3
|     
4    

4 = 0 
2 = 1
3 = 0 
1 = 2 



Skewed Binary Trees
In this lesson, we will discuss another type of Binary Tree called Skewed Binary Tree. We will look at some of its properties and types.

Introduction 
The binary tree in which each node has either one or no child is known as a skewed binary tree. In this type of tree, either all nodes are positioned to the left or the right. 
This type of Binary Tree structure should be avoided at all costs because the time complexity of most operations will be high.

There are two types of Skewed Binary Trees based on which side the tree leans towards.

Left-Skewed Binary Trees
Right-Skewed Binary Trees
Left-Skewed Binary Trees 
The left-skewed binary tree has all left child nodes.

Right-Skewed Binary Trees 
Right skewed binary trees have all right nodes.
