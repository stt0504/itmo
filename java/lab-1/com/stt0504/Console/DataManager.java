package com.stt0504.Console;

import com.stt0504.Account.Account;
import com.stt0504.Bank.Bank;
import com.stt0504.User.User;

/**
 * The DataManager class represents a manager for handling data related to banks, users, and accounts.
 */
public class DataManager {

    /** The bank currently in use. */
    public Bank bank;

    /** The user currently interacting with the system. */
    public User user;

    /** The account currently selected for operations. */
    public Account account;
}
