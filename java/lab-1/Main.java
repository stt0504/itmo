import com.stt0504.Bank.Bank;
import com.stt0504.Console.AccountActions.*;
import com.stt0504.Console.Action;
import com.stt0504.Console.BankActions.AddAccountAction;
import com.stt0504.Console.BankActions.LoginAction;
import com.stt0504.Console.BankActions.RegistrationAction;
import com.stt0504.Console.ChoiceActions.ChoiceOfAccount;
import com.stt0504.Console.ChoiceActions.ChoiceOfAction;
import com.stt0504.Console.ChoiceActions.ChoiceOfBank;
import com.stt0504.Console.DataManager;
import com.stt0504.Console.ExitAction;


import java.util.*;

public class Main {

    public static void main(String[] args) {
        Bank bank1 = new Bank("bank1", 20, new TreeMap<>() {{
            put(100.0, 2.0);
            put(500.0, 3.0);
        }}, 3.65, 10000, 10000, 8000);

        Bank bank2 = new Bank("bank2", 30, new TreeMap<>() {{
            put(100.0, 3.0);
            put(1000.0, 4.0);
        }}, 10, 10000, 10000, 8000);

        Action refillAction = new RefillAction("refill");
        Action showBalanceAtDateAction = new ShowBalanceAtDateAction("show balance at date");
        Action transactionHistoryAction = new TransactionHistoryAction("show transaction history");
        Action transferAction = new TransferAction("transfer");
        Action withdrawAction = new WithdrawAction("withdraw");

        ChoiceOfAction operationChoice = new ChoiceOfAction("operation choice");
        operationChoice.AddChoices(List.of(refillAction,
                showBalanceAtDateAction,
                transactionHistoryAction,
                transferAction,
                withdrawAction));
        operationChoice.Message("Select an action: ");
        operationChoice.UseConverter(x -> x.name);

        refillAction.next = operationChoice;
        showBalanceAtDateAction.next = operationChoice;
        transactionHistoryAction.next = operationChoice;
        transferAction.next = operationChoice;
        withdrawAction.next = operationChoice;

        ChoiceOfAccount accountChoiceAction = new ChoiceOfAccount("Choose account");
        accountChoiceAction.Message("Choose account: ");
        accountChoiceAction.UseConverter(x -> x.getID() +x.getClass().getName());
        accountChoiceAction.next = operationChoice;

        ChoiceOfAction accountAction = new ChoiceOfAction("choice of account action");
        AddAccountAction accountRegisterAction = new AddAccountAction("add account action");
        accountRegisterAction.next = accountAction;

        ChoiceOfAction authorizationChoice = new ChoiceOfAction("authorization");
        RegistrationAction registrationAction = new RegistrationAction("Register");
        registrationAction.next = authorizationChoice;

        accountAction.AddChoices(List.of(accountChoiceAction, accountRegisterAction));
        accountAction.Message("Select an action: ");
        accountAction.UseConverter(x -> x.name);

        LoginAction Login = new LoginAction("Login");
        Login.next = accountAction;

        authorizationChoice.UseConverter(x -> x.name);
        authorizationChoice.AddChoices(List.of(registrationAction,
                        Login));
        authorizationChoice.Message("Select an action: ");

        ChoiceOfBank bankChoiceAction = new ChoiceOfBank("Choose bank");
        bankChoiceAction.next = authorizationChoice;
        bankChoiceAction.AddChoices(List.of(bank1, bank2));
        bankChoiceAction.Message("Select bank: ");
        bankChoiceAction.UseConverter(Bank::getName);

        ChoiceOfAction main = new ChoiceOfAction("main");
        main.manager = new DataManager();
        main.AddChoices(Arrays.asList(bankChoiceAction, new ExitAction("Exit")));
        main.Message("Select an action: ");
        main.UseConverter(x -> x.name);

        main.Run();
    }
}