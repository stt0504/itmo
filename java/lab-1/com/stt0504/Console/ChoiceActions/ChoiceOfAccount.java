package com.stt0504.Console.ChoiceActions;

import com.stt0504.Account.Account;

/**
 * The ChoiceOfAccount class represents an action to choose an account from a list of accounts.
 * It extends the Choice class and provides a method to run the action by presenting available accounts to the user.
 */
public class ChoiceOfAccount extends Choice<Account> {

    /**
     * Constructor for ChoiceOfAccount class.
     * @param name The name of the choice action.
     */
    public ChoiceOfAccount(String name) {
        super(name);
    }

    /**
     * Runs the action by presenting available accounts to the user and allowing them to choose one.
     * Sets the chosen account to the next action's data manager.
     */
    public void Run() {
        // Retrieve the list of accounts available to the user
        choices = manager.bank.GetAccounts(manager.user);

        // Allow the user to choose an account from the list
        Choose();

        // Set the chosen account to the next action's data manager
        next.manager = manager;
        next.manager.account = choice;

        // Execute the next action
        next.Run();
    }
}
