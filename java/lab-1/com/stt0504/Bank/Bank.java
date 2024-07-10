package com.stt0504.Bank;

import com.stt0504.Account.*;
import com.stt0504.User.User;

import java.time.LocalDate;
import java.util.*;

/**
 * The Bank class represents a bank that manages user accounts and transactions.
 */
public class Bank {
    private final String _name;
    private final NavigableMap<Double, Double> _percents;
    private final double debitPercent;
    private final double creditLimit;
    private final double _commission;
    private final Map<User, List<Account>> users = new HashMap<>();
    private double withdrawLimit;
    private double transferLimit;
    private int counter = 0;
    private Vector<User> subscribers;

    /**
     * Constructor for creating a Bank object.
     *
     * @param name         The name of the bank.
     * @param commission   The commission rate for credit accounts if they have a negative balance.
     * @param percents     The percentage rates for different balance of deposit accounts.
     * @param debitPercent The percentage rate for debit accounts.
     * @param creditLimit  The limit of credit for credit accounts.
     */
    public Bank(String name, double commission, NavigableMap<Double, Double> percents, double debitPercent, double creditLimit, double withdrawLimit, double transferLimit) {
        _name = name;
        _commission = commission;
        _percents = percents;
        this.debitPercent = debitPercent;
        this.creditLimit = creditLimit;
        this.withdrawLimit = withdrawLimit;
        this.transferLimit = transferLimit;
    }

    /**
     * Creates an account for a user based on the specified account type.
     *
     * @param user The user for whom the account is created.
     * @param type The type of account to be created (e.g., CREDIT, DEBIT, DEPOSIT).
     */
    public void CreateAccount(User user, AccountType type, LocalDate startDate, LocalDate endDate, double balance) {
        counter++;
        Account account = switch (type) {
            case CREDIT -> new CreditAccount(counter, startDate, endDate, creditLimit, _commission, user, balance);
            case DEBIT -> new DebitAccount(counter, startDate, endDate, debitPercent, user, balance);
            case DEPOSIT -> {
                Map.Entry<Double, Double> entry = _percents.floorEntry(balance);
                yield new DepositAccount(counter, startDate, endDate, entry.getValue(), user, balance);
            }
        };
        users.computeIfAbsent(user, k -> new ArrayList<>()).add(account);
    }

    /**
     * Finds a user based on the login credentials.
     *
     * @param login    The user's login.
     * @param password The user's password.
     * @return The user if found, otherwise null.
     */
    public User FindUser(String login, String password) {
        for (Map.Entry<User, List<Account>> entry : users.entrySet()) {
            User user = entry.getKey();
            if (user.getLogin().equals(login) && user.getPassword().equals(password)) {
                return user;
            }
        }
        return null;
    }

    /**
     * Gets the list of accounts associated with a user.
     *
     * @param user The user whose accounts are to be retrieved.
     * @return The list of accounts associated with the user.
     */
    public List<Account> GetAccounts(User user) {
        return users.getOrDefault(user, new ArrayList<>());
    }

    /**
     * Adds an account to the list of accounts associated with a user.
     * @param user    The user to whom the account belongs.
     */

    public Account GetAccount(User user, int id) {
        List<Account> accounts = GetAccounts(user);
        for (Account account : accounts) {
            if (account.getID() == id) {
                return account;
            }
        }
        return null;
    }

    public void AddAccount(Account account, User user) {
        users.computeIfAbsent(user, k -> new ArrayList<>()).add(account);
    }

    /**
     * Adds a new user to the bank's user database.
     *
     * @param user The user to be added.
     */
    public void AddUser(User user) {
        users.put(user, new ArrayList<>());
    }

    /**
     * Updates all accounts in the bank.
     */
    public void Update() {
        for (Map.Entry<User, List<Account>> entry : users.entrySet()) {
            for (Account account : entry.getValue()) {
                account.Update();
            }
        }
    }

    /**
     * Refills the balance of an account with the specified amount.
     *
     * @param account The account to be refilled.
     * @param amount  The amount to be added to the account balance.
     */
    public void Refill(Account account, double amount) {
        account.Refill(amount);
    }

    /**
     * Withdraws the specified amount from an account.
     *
     * @param account The account from which the amount is to be withdrawn.
     * @param amount  The amount to be withdrawn.
     */
    public void Withdraw(Account account, double amount) {
        if (account.getOwner().IsQuestionable() || amount <= withdrawLimit) {
            account.Withdraw(amount);
        } else {
            throw new IllegalArgumentException("User is questionable; withdraw limit exceeded");
        }
    }

    /**
     * Transfers funds from one account to another.
     *
     * @param sender   The account from which funds are to be transferred.
     * @param receiver The account to which funds are to be transferred.
     * @param amount   The amount to be transferred.
     */
    public void Transfer(Account sender, Account receiver, double amount) {
        List<Account> senderAccounts = users.get(sender.getOwner());
        List<Account> receiverAccounts = users.get(receiver.getOwner());
        if (senderAccounts != null && receiverAccounts != null && (sender.getOwner().IsQuestionable() || amount <= transferLimit)) {
            sender.Withdraw(amount);
            receiver.Refill(amount);
        } else {
            throw new IllegalArgumentException("User is questionable; transfer limit exceeded");
        }
    }

    /**
     * Sets the withdrawal limit for bank transactions.
     *
     * @param withdrawLimit The withdrawal limit to be set.
     */
    public void setWithdrawLimit(double withdrawLimit) {
        this.withdrawLimit = withdrawLimit;
        notifySubscribers();
    }

    /**
     * Sets the transfer limit for bank transactions.
     *
     * @param transferLimit The transfer limit to be set.
     */
    public void setTransferLimit(double transferLimit) {
        this.transferLimit = transferLimit;
        notifySubscribers();
    }

    /**
     * Subscribes a user to receive notifications from the bank.
     *
     * @param user The user to be subscribed.
     */
    public void subscribe(User user) {
        subscribers.add(user);
    }

    /**
     * Unsubscribes a user from receiving notifications from the bank.
     *
     * @param user The user to be unsubscribed.
     */
    public void unsubscribe(User user) {
        subscribers.remove(user);
    }

    /**
     * Notifies subscribers of any updates or changes in the bank.
     */
    public void notifySubscribers() {
        for (User subscriber : subscribers) {
            subscriber.receiveNotification();
        }
    }

    /**
     * Retrieves the name of the bank.
     *
     * @return The name of the bank.
     */
    public String getName() {
        return _name;
    }
}
