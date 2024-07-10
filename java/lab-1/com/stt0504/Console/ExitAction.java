package com.stt0504.Console;

/**
 * The ExitAction class represents an action to exit the console application.
 * It extends the Action class and provides a method to terminate the application.
 */
public class ExitAction extends Action {

    /**
     * Constructor for ExitAction class.
     * @param name The name of the exit action.
     */
    public ExitAction(String name) {
        super(name);
    }

    /**
     * Overrides the Run method from the Action class to terminate the application.
     */
    public void Run() {
        System.exit(0);
    }
}
