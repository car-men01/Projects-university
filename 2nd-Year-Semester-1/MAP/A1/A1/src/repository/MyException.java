package repository;
import java.lang.Exception;

public class MyException extends Exception {
    String message;
    public MyException(String text){
        this.message = text;
    }

    public String getMessage() {
        return this.message;
    }

    public String toString(){
        return "Error: " + this.message;
    }
}
