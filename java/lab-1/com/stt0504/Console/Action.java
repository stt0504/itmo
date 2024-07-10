package com.stt0504.Console;

/**
 * The Action class represents an abstract action that can be performed in the console.
 * Subclasses of Action define specific actions to be executed.
 */
public abstract class Action {

    /** The name of the action. */
    public String name;

    /** The next action to be executed. */
    public Action next;

    /** The data manager used for performing actions. */
    public DataManager manager;

    /**
     * Constructor for the Action class.
     * @param name The name of the action.
     */
    public Action(String name) {
        this.name = name;
    }

    /**
     * Abstract method Run defines the behavior to be executed when the action is performed.
     */
    public abstract void Run();
}
