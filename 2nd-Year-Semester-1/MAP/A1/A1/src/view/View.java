package view;

import model.*;
import repository.*;
import controller.*;

import java.util.Scanner;

public class View {
    private Controller controller;

    public View(Controller controller) {
        this.controller = controller;
    }
    public static void menu() {
        System.out.println("\n1. Add tree");
        System.out.println("2. Delete tree");
        System.out.println("3. Show all trees");
        System.out.println("4. Show trees older than 3 years");
        System.out.println("0. Exit\n");
    }

    public void viewAdd(String type, String name, int age) throws MyException {
        if (type.equals("Apple") || type.equals("apple")) {
            AppleTree tree = new AppleTree(name, age);
            int res = this.controller.addTree(tree);
            if (res == 1)
                System.out.println("Tree added successfully!");
        }
        else if (type.equals("Pear") || type.equals("pear")) {
            PearTree tree = new PearTree(name, age);
            int res = this.controller.addTree(tree);
            if (res == 1)
                System.out.println("Tree added successfully!");
        }
        else if (type.equals("Cherry") || type.equals("cherry")) {
            CherryTree tree = new CherryTree(name, age);
            int res = this.controller.addTree(tree);
            if (res == 1)
                System.out.println("Tree added successfully!");
        }
        else {
            System.out.println("Invalid tree type!");
        }
    }

    public void viewDelete(int index) throws MyException {
        int res = this.controller.deleteTree(index);
        if (res == 1)
            System.out.println("Tree deleted successfully!");
    }

    public void showAllTrees() {
        Tree[] trees = this.controller.getTrees();
        int i = 0;
        for (Tree tree : trees) {
            System.out.println(i + ". " + tree);
            i++;
        }
    }

    public void showTreesOlderThan3Years() {
        Tree[] trees = this.controller.getTreesOlderThan3Years();
        int i = 0;
        for (Tree tree : trees) {
            System.out.println(i + ". " + tree);
            i++;
        }
    }

    public void application() throws MyException {
        while(true) {
            View.menu();
            int option;
            Scanner scanner = new Scanner(System.in);
            System.out.print("Enter an option from the menu: ");
            option = scanner.nextInt();

            if (option == 0) {
                break;
            }
            else if (option == 1) {
                System.out.print("Enter the type of the tree (Apple/Pear/Cherry): ");
                String type = scanner.next();
                System.out.print("Tree name: ");
                String name = scanner.next();
                System.out.print("Tree age: ");
                int age = scanner.nextInt();
                this.viewAdd(type, name, age);

            }
            else if (option == 2) {
                System.out.print("Enter the index of the tree you want to delete: ");
                int index = scanner.nextInt();
                this.viewDelete(index);
            }
            else if (option == 3) {
                this.showAllTrees();
            }
            else if (option == 4) {
                this.showTreesOlderThan3Years();
            }
            else {
                System.out.println("Invalid option!");
            }
        }
    }
}
