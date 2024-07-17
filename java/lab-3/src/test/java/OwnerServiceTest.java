import com.stt0504.*;
import com.stt0504.Dao.OwnerDAO;
import com.stt0504.Entities.Owner;
import org.junit.jupiter.api.Test;

import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

import static org.junit.jupiter.api.Assertions.*;
import static org.mockito.Mockito.*;

public class OwnerServiceTest {

    @Test
    public void getOwners() {
        OwnerDAO dao = mock(OwnerDAO.class);
        List<Owner> owners = new ArrayList<>();
        owners.add(new Owner().setName("Name1").setCats(new ArrayList<>()));
        owners.add(new Owner().setName("Name2").setCats(new ArrayList<>()));
        when(dao.findAll()).thenReturn(owners);
        OwnerService service = new OwnerService(dao);

        List<OwnerDTO> result = service.getOwners();

        List<OwnerDTO> expected = new ArrayList<>();
        expected.add(new OwnerDTO().setName("Name1"));
        expected.add(new OwnerDTO().setName("Name2"));

        for (int i = 0; i < expected.size(); i++) {
            assertEquals(expected.get(i).getName(), result.get(i).getName());
        }
    }

    @Test
    public void getOwnerById() {
        OwnerDAO dao = mock(OwnerDAO.class);
        Owner owner = new Owner().setName("Name1").setId(1L).setCats(new ArrayList<>());
        when(dao.findById(1L)).thenReturn(Optional.of(owner));
        OwnerService service = new OwnerService(dao);
        OwnerDTO result = service.getOwnerById(1L);

        OwnerDTO expected = new OwnerDTO().setName("Name1").setId(1L);

        assertEquals(expected.getName(), result.getName());
    }

    @Test
    public void AddOwnerTest_Failed_NameIsEmpty() {
        OwnerDAO dao = mock(OwnerDAO.class);

        List<Owner> owners = new ArrayList<>();
        Owner owner1 = new Owner().setName("");

        doAnswer(invocation -> {
            owners.add(owner1);
            return null;
        }).when(dao).save(owner1);

        OwnerService service = new OwnerService(dao);

        OwnerDTO ownerDTO = new OwnerDTO().setName("");
        assertThrows(IllegalArgumentException.class, () -> service.addOwner(ownerDTO));

        assertFalse(owners.contains(owner1));
    }

    @Test
    public void AddOwnerTest_Success() {
        OwnerDAO dao = mock(OwnerDAO.class);

        List<Owner> owners = new ArrayList<>();
        Owner owner1 = new Owner().setName("Name1");

        doAnswer(invocation -> {
            owners.add(owner1);
            return null;
        }).when(dao).save(owner1);

        OwnerService service = new OwnerService(dao);

        OwnerDTO ownerDTO = new OwnerDTO().setName("Name1");
        assertDoesNotThrow(() -> service.addOwner(ownerDTO));
    }
}