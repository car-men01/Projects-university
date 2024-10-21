package repository;

import model.*;

public interface Repository {
    void addTree(Tree tree) throws MyException;
    void deleteTree(int index) throws MyException;
    Tree[] getTrees();
}


