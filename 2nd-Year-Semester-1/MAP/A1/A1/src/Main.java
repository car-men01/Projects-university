import controller.*;
import model.*;
import repository.*;
import view.*;

public class Main {

    public static void main(String[] args) throws MyException {

        /*
        6. Intr-o livada cresc meri, peri si ciresi.
        Sa se afiseze toti pomii frunctiferi mai batrani de 3 ani.
        */

        //AppleTree
        AppleTree appleTree1 = new AppleTree("Fuji", 2);
        AppleTree appleTree2 = new AppleTree("Gala", 1);
        AppleTree appleTree3 = new AppleTree("Granny Smith", 6);
        AppleTree appleTree4 = new AppleTree("Red Delicious", 9);

        //PearTree
        PearTree pearTree1 = new PearTree("Anjou", 7);
        PearTree pearTree2 = new PearTree("Comice", 3);
        PearTree pearTree3 = new PearTree("Seckel", 4);

        //CherryTree
        CherryTree cherryTree1 = new CherryTree("Cherry blossom", 2);
        CherryTree cherryTree2 = new CherryTree("Stella", 0);
        CherryTree cherryTree3 = new CherryTree("Sakura", 5);
        CherryTree cherryTree4 = new CherryTree("Sour cherry", 8);

        InMemoryRepo repository = new InMemoryRepo(13);
        Controller controller = new Controller(repository);
        View view = new View(controller);

        controller.addTree(appleTree1);
        controller.addTree(appleTree2);
        controller.addTree(appleTree3);
        controller.addTree(appleTree4);
        controller.addTree(pearTree1);
        controller.addTree(pearTree2);
        controller.addTree(pearTree3);
        controller.addTree(cherryTree1);
        controller.addTree(cherryTree2);
        controller.addTree(cherryTree3);
        controller.addTree(cherryTree4);

        view.application();
    }
}