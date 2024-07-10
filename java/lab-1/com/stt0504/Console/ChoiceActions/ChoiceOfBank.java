package com.stt0504.Console.ChoiceActions;

import com.stt0504.Bank.Bank;

/**
 * The ChoiceOfBank class represents an action to choose a bank from a list of available banks.
 * It extends the Choice class and provides a method to run the action by presenting available banks to the user.
 */
public class ChoiceOfBank extends Choice<Bank> {

    /**
     * Constructor for ChoiceOfBank class.
     * @param name The name of the choice action.
     */
    public ChoiceOfBank(String name) {
        super(name);
    }

    /**
     * Runs the action by presenting available banks to the user and allowing them to choose one.
     * Sets the chosen bank to the next action's data manager.
     */
    public void Run() {
        // Allow the user to choose a bank from the list of available banks
        Choose();

        // Set the chosen bank to the next action's data manager
        next.manager = manager;
        next.manager.bank = choice;

        // Execute the next action
        next.Run();
    }
}
