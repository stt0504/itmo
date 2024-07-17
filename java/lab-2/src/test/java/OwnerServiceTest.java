import com.stt0504.*;
import org.junit.jupiter.api.Test;

import java.util.ArrayList;
import java.util.List;

import static org.junit.jupiter.api.Assertions.*;
import static org.mockito.Mockito.*;

public class OwnerServiceTest {

    @Test
    public void getOwners() {
        OwnerDAO dao = mock(OwnerDAO.class);
        List<Owner> owners = new ArrayList<>();
        owners.add(new Owner().setName("Name1").setCats(new ArrayList<>()));
        owners.add(new Owner().setName("Name2").setCats(new ArrayList<>()));
        when(dao.getAllOwners()).thenReturn(owners);
        OwnerService service = new OwnerService(dao);
        List<OwnerDTO> result = service.getOwners();

        List<OwnerDTO> ownerDTOs = new ArrayList<>();
        ownerDTOs.add(new OwnerDTO().setName("Name1"));
        ownerDTOs.add(new OwnerDTO().setName("Name2"));

        List<OwnerDTO> expected = service.getOwners();
        for (int i = 0; i < ownerDTOs.size(); i++) {
            assertEquals(expected.get(i).getName(), result.get(i).getName());
        }
    }

    @Test
    public void getOwnerById() {
        OwnerDAO dao = mock(OwnerDAO.class);
        Owner owner = new Owner().setName("Name1").setId(1L).setCats(new ArrayList<>());
        when(dao.getOwnerById(1L)).thenReturn(owner);
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
        }).when(dao).addOwner(owner1);

        OwnerService service = new OwnerService(dao);

        OwnerDTO ownerDTO = new OwnerDTO().setName("");
        assertThrows(IllegalArgumentException.class, () -> service.addOwner(ownerDTO));

        assertFalse(owners.contains(owner1));
    }

    @Test
    public void AddOwnerTest_Success() {
        OwnerDAO dao = mock(OwnerDAO.class);

        List<Owner> owners = new ArrayList<>();
        Owner owner1 = new Owner().setName("Name1").setCats(new ArrayList<>());

        doAnswer(invocation -> {
            owners.add(owner1);
            return owner1;
        }).when(dao).addOwner(any());

        OwnerService service = new OwnerService(dao);

        OwnerDTO ownerDTO = new OwnerDTO().setName("Name1");
        assertDoesNotThrow(() -> service.addOwner(ownerDTO));
    }
}