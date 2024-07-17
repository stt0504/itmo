import com.stt0504.*;
import com.stt0504.Commands.*;
import org.hibernate.SessionFactory;
import org.hibernate.cfg.Configuration;

import java.util.ArrayList;
import java.util.List;

public class Main {

    public static void main(String[] args) {
        Configuration configuration = new Configuration().configure("hibernate.cfg.xml");

        SessionFactory sessionFactory = configuration.buildSessionFactory();

        CatDAO catDAO = new CatDAO(sessionFactory);
        OwnerDAO ownerDAO = new OwnerDAO(sessionFactory);
        ColorConverter converter = new ColorConverter();

        CatService catService = new CatService(catDAO, ownerDAO, converter);
        OwnerService ownerService = new OwnerService(ownerDAO);

        List<Command> commands = new ArrayList<>();
        commands.add(new AddCatCommand(catService));
        commands.add(new AddFriendshipCommand(catService));
        commands.add(new AddOwnerCommand(ownerService));
        commands.add(new ShowAllCatsCommand(catService));
        commands.add(new ShowCatInfoCommand(catService));
        commands.add(new ShowOwnerInfoCommand(ownerService, catService));
        ConsoleController consoleController = new ConsoleController(commands);
        consoleController.start();

        sessionFactory.close();
    }
}
