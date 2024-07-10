package com.stt0504.Console.ChoiceActions;

import com.stt0504.Console.Action;

/**
 * The ChoiceOfAction class represents an action to choose from a list of available actions.
 * It extends the Choice class and provides a method to run the action by presenting available actions to the user.
 */
public class ChoiceOfAction extends Choice<Action> {

    /**
     * Constructor for ChoiceOfAction class.
     * @param name The name of the choice action.
     */
    public ChoiceOfAction(String name) {
        super(name);
    }

    /**
     * Runs the action by presenting available actions to the user and allowing them to choose one.
     * Sets the chosen action as the next action to be executed.
     */
    public void Run() {
        // Allow the user to choose an action from the list of available actions
        Choose();

        // Set the chosen action as the next action to be executed
        next = choice;

        // Set the data manager of the next action
        next.manager = manager;

        // Execute the next action
        next.Run();
    }
}
