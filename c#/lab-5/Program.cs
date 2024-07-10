using System.Collections.ObjectModel;
using Lab05.Entities.DatabaseManager;
using Lab05.Entities.Scenarios;
using Lab05.Entities.Scenarios.AdminOperations;
using Lab05.Entities.Scenarios.UserOperations;
using Lab05.Services;

namespace Lab05;

public static class Program
{
    public static void Main(string[] args)
    {
        if (args is null) throw new ArgumentNullException(nameof(args));
        string systemPassword = args[0];
        const string connectionString = "Host=localhost;Port=5432;Username=postgres;Password=postgres;Database=postgres";

        IDataManager manager = new DatabaseManager(connectionString);
        var userService = new UserService(manager);
        var adminService = new AdminService(systemPassword, manager);

        var backScenario = new GoBackScenario();

        var addMoneyScenario = new AddMoneyScenario(userService);
        var viewBalanceScenario = new ViewBalanceScenario(userService);
        var viewHistoryScenario = new ViewHistoryScenario(userService);
        var withdrawMoneyScenario = new WithdrawMoneyScenario(userService);

        var viewBalanceScenarioAdmin = new ViewBalanceScenarioAdmin(adminService);
        var viewHistoryScenarioAdmin = new ViewHistoryScenarioAdmin(adminService);

        var userOperationsScenarios = new Collection<IScenario>
        {
            addMoneyScenario,
            viewBalanceScenario,
            viewHistoryScenario,
            withdrawMoneyScenario,
            backScenario,
        };

        var adminOperationsScenarios = new Collection<IScenario>
        {
            viewBalanceScenarioAdmin,
            viewHistoryScenarioAdmin,
            backScenario,
        };

        var userOperationsScenario = new UserOperationsChoiceScenario(userOperationsScenarios);
        var adminOperationsScenario = new AdminOperationsChoiceScenario(adminOperationsScenarios);

        addMoneyScenario.SetNext(userOperationsScenario);
        viewBalanceScenario.SetNext(userOperationsScenario);
        viewHistoryScenario.SetNext(userOperationsScenario);
        withdrawMoneyScenario.SetNext(userOperationsScenario);

        viewBalanceScenarioAdmin.SetNext(adminOperationsScenario);
        viewHistoryScenarioAdmin.SetNext(adminOperationsScenario);

        var createAccountScenario = new CreateAccountScenario(userService);
        var userLoginScenario = new UserLoginScenario(userService);
        var adminLoginScenario = new AdminLoginScenario(adminService);

        var firstScenarios = new Collection<IScenario>
        {
            createAccountScenario,
            userLoginScenario,
            adminLoginScenario,
        };

        var firstScenario = new AuthorizationChoiceScenario(firstScenarios);

        createAccountScenario.SetNext(firstScenario);
        userLoginScenario.SetNext(userOperationsScenario);
        adminLoginScenario.SetNext(adminOperationsScenario);
        backScenario.SetNext(firstScenario);

        while (true)
        {
            firstScenario.Run();
        }
    }
}