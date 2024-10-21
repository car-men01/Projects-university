package repository;

import model.Tree;

public class InMemoryRepo implements Repository{
    public Tree[] trees;
    int count;

    public InMemoryRepo(int size) {
        this.count = 0;
        this.trees = new Tree[size];
    }

    public void addTree(Tree tree) throws MyException {
        if (this.count == trees.length)
            throw new MyException("The list is full");
        this.trees[this.count] = tree;
        this.count++;
    }

    public void deleteTree(int index) throws MyException {
        if (index < 0 || index >= this.count)
            throw new MyException("Invalid index");
        for (int i = index; i < this.count - 1; i++) {
            this.trees[i] = this.trees[i + 1];
        }
        this.count--;
    }

    public Tree[] getTrees() {
        Tree[] result = new Tree[this.count];
        for (int i = 0; i < this.count; i++) {
            result[i] = this.trees[i];
        }
        return result;
    }
}
