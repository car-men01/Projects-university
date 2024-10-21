package controller;

import model.*;
import repository.*;

public class Controller {
    private Repository repository;

    public Controller(Repository repository) {
        this.repository = repository;
    }

    public int addTree(Tree tree) throws MyException {
        try {
            repository.addTree(tree);
            return 1;
        } catch (MyException e) {
            System.out.println(e.getMessage());
            return -1;
        }
    }

    public int deleteTree(int index) throws MyException {
        try {
            repository.deleteTree(index);
            return 1;
        } catch (MyException e) {
            System.out.println(e.getMessage());
            return -1;
        }
    }

    public Tree[] getTrees() {
        return repository.getTrees();
    }

    public Tree[] getTreesOlderThan3Years() {
        Tree[] allTrees = repository.getTrees();
        return filterOlderTrees(allTrees);
    }

    private Tree[] filterOlderTrees(Tree[] trees) {
        int count = 0;
        for (Tree tree : trees) {
            if (tree != null && tree.isOlderThan3Years()) {
                count++;
            }
        }
        Tree[] result = new Tree[count];
        int index = 0;
        for (Tree tree : trees) {
            if (tree.isOlderThan3Years()) {
                result[index++] = tree;
            }
        }
        return result;
    }
}
