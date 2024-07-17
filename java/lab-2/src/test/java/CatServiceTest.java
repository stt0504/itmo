import com.stt0504.*;
import org.junit.jupiter.api.Test;

import java.time.LocalDate;
import java.util.ArrayList;
import java.util.List;

import static org.junit.jupiter.api.Assertions.*;
import static org.mockito.Mockito.*;

public class CatServiceTest {

    @Test
    public void getAllCats() {
        CatDAO dao = mock(CatDAO.class);
        List<Cat> cats = new ArrayList<>();

        Owner owner1 = new Owner().setName("Owner1");
        cats.add(new Cat().setName("Cat1").setBreed("Breed1").setOwner(owner1));
        cats.add(new Cat().setName("Cat2").setBreed("Breed2").setOwner(owner1));
        when(dao.getAllCats()).thenReturn(cats);

        OwnerDAO dao2 = mock(OwnerDAO.class);

        ColorConverter converter = new ColorConverter();

        CatService service = new CatService(dao, dao2, converter);

        List<CatDTO> catDTOs = new ArrayList<>();
        catDTOs.add(new CatDTO().setName("Cat1").setBreed("Breed1").setOwnerId(owner1.getId()));
        catDTOs.add(new CatDTO().setName("Cat2").setBreed("Breed2").setOwnerId(owner1.getId()));

        List<CatDTO> result = service.getAllCats();
        for (int i = 0; i < catDTOs.size(); i++) {
            assertEquals(catDTOs.get(i).getName(), result.get(i).getName());
        }
    }

    @Test
    public void getCatById() {
        CatDAO dao = mock(CatDAO.class);
        Cat cat = new Cat().setName("Cat1").setId(1L);
        when(dao.getCatById(1L)).thenReturn(cat);

        OwnerDAO dao2 = mock(OwnerDAO.class);

        ColorConverter converter = new ColorConverter();

        CatService service = new CatService(dao, dao2, converter);
        CatDTO result = service.getCatById(1L);

        CatDTO expected = new CatDTO().setName("Cat1").setId(1L);
        assertEquals(expected.getName(), result.getName());
    }

    @Test
    public void AddCatTest_Failed_NoSuchOwner() {
        CatDAO dao = mock(CatDAO.class);

        List<Cat> cats = new ArrayList<>();
        Cat cat1 = new Cat().setName("Name1")
                .setBirthDate(LocalDate.of(2000, 1, 1))
                .setOwner(new Owner().setName("Owner1").setId(1L));

        doAnswer(invocation -> {
            cats.add(cat1);
            return cat1;
        }).when(dao).addCat(cat1);


        OwnerDAO dao2 = mock(OwnerDAO.class);
        when(dao2.getOwnerById(1L)).thenReturn(null);

        ColorConverter converter = new ColorConverter();

        CatService service = new CatService(dao, dao2, converter);

        CatDTO catDTO = new CatDTO().setName("Name1")
                .setBirthDate(LocalDate.of(2000, 1, 1))
                .setOwnerId(1L);

        assertThrows(IllegalArgumentException.class, () -> service.addCat(catDTO));

        assertFalse(cats.contains(cat1));
    }

    @Test
    public void AddCatTest_Failed_BirthDateIsNull() {
        CatDAO dao = mock(CatDAO.class);

        Owner owner1 = new Owner().setName("Owner1");
        List<Cat> cats = new ArrayList<>();
        Cat cat1 = new Cat().setName("Name1")
                .setOwner(owner1);

        doAnswer(invocation -> {
            cats.add(cat1);
            return cat1;
        }).when(dao).addCat(cat1);

        OwnerDAO dao2 = mock(OwnerDAO.class);
        when(dao2.getOwnerById(1L)).thenReturn(owner1);

        ColorConverter converter = new ColorConverter();

        CatService service = new CatService(dao, dao2, converter);

        CatDTO catDTO = new CatDTO().setName("Name1")
                .setOwnerId(owner1.getId());
        assertThrows(IllegalArgumentException.class, () -> service.addCat(catDTO));

        assertFalse(cats.contains(cat1));
    }

    @Test
    public void AddCatTest_Failed_NameIsEmpty() {
        CatDAO dao = mock(CatDAO.class);

        Owner owner1 = new Owner().setName("Owner1");
        List<Cat> cats = new ArrayList<>();
        Cat cat1 = new Cat().setName("")
                .setBirthDate(LocalDate.of(2000, 1, 1))
                .setOwner(owner1);

        doAnswer(invocation -> {
            cats.add(cat1);
            return cat1;
        }).when(dao).addCat(cat1);

        OwnerDAO dao2 = mock(OwnerDAO.class);
        when(dao2.getOwnerById(1L)).thenReturn(owner1);

        ColorConverter converter = new ColorConverter();

        CatService service = new CatService(dao, dao2, converter);


        CatDTO catDTO = new CatDTO().setName("")
                .setBirthDate(LocalDate.of(2000, 1, 1))
                .setOwnerId(owner1.getId());
        assertThrows(IllegalArgumentException.class, () -> service.addCat(catDTO));

        assertFalse(cats.contains(cat1));
    }

    @Test
    public void AddCatTest_Success() {
        CatDAO dao = mock(CatDAO.class);

        Owner owner1 = new Owner().setName("Owner1").setId(1L);
        List<Cat> cats = new ArrayList<>();
        Cat cat1 = new Cat().setName("Name1")
                .setBirthDate(LocalDate.of(2000, 1, 1))
                .setOwner(owner1);

        OwnerDAO dao2 = mock(OwnerDAO.class);
        when(dao2.getOwnerById(1L)).thenReturn(owner1);

        ColorConverter converter = new ColorConverter();

        CatService service = new CatService(dao, dao2, converter);


        CatDTO catDTO = new CatDTO().setName("Name1")
                .setBirthDate(LocalDate.of(2000, 1, 1))
                .setOwnerId(owner1.getId());

        doAnswer(invocation -> {
            cats.add(cat1);
            return cat1;
        }).when(dao).addCat(any());

        assertDoesNotThrow(() -> service.addCat(catDTO));
        assertTrue(cats.contains(cat1));
    }

    @Test
    public void AddFriendshipTest_Success() {
        CatDAO dao = mock(CatDAO.class);

        List<Cat> cats = new ArrayList<>();
        cats.add(new Cat().setName("Cat1").setBreed("Breed1"));
        cats.add(new Cat().setName("Cat2").setBreed("Breed2"));

        when(dao.getCatById(1L)).thenReturn(cats.get(0));
        when(dao.getCatById(2L)).thenReturn(cats.get(1));

        doAnswer(invocation -> {
            cats.get(0).getFriends().add(cats.get(1));
            cats.get(1).getFriends().add(cats.get(0));
            return null;
        }).when(dao).addFriendship(1L, 2L);

        OwnerDAO dao2 = mock(OwnerDAO.class);

        ColorConverter converter = new ColorConverter();

        CatService service = new CatService(dao, dao2, converter);

        assertDoesNotThrow(() -> service.addFriendship(1L, 2L));

        assertTrue(cats.get(0).getFriends().contains(cats.get(1)));
        assertTrue(cats.get(1).getFriends().contains(cats.get(0)));
    }

    @Test
    public void AddFriendshipTest_Failed() {
        CatDAO dao = mock(CatDAO.class);

        List<Cat> cats = new ArrayList<>();
        cats.add(new Cat().setName("Cat1").setBreed("Breed1"));
        cats.add(new Cat().setName("Cat2").setBreed("Breed2"));

        when(dao.getCatById(1L)).thenReturn(cats.get(0));
        when(dao.getCatById(2L)).thenReturn(cats.get(1));

        doAnswer(invocation -> {
            cats.get(0).getFriends().add(cats.get(1));
            cats.get(1).getFriends().add(cats.get(0));
            return null;
        }).when(dao).addFriendship(1L, 2L);

        OwnerDAO dao2 = mock(OwnerDAO.class);

        ColorConverter converter = new ColorConverter();

        CatService service = new CatService(dao, dao2, converter);

        assertThrows(IllegalArgumentException.class, () -> {
            service.addFriendship(1L, 2L);
            service.addFriendship(1L, 2L);
        });

        assertTrue(cats.get(0).getFriends().contains(cats.get(1)));
        assertTrue(cats.get(1).getFriends().contains(cats.get(0)));
    }
}