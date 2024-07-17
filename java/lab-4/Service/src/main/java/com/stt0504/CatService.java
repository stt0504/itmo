package com.stt0504;

import com.stt0504.Dao.CatDAO;
import com.stt0504.Dao.FriendshipDAO;
import com.stt0504.Dao.OwnerDAO;
import com.stt0504.Entities.Cat;
import com.stt0504.Entities.CatFriendship;
import com.stt0504.Entities.Color;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.ArrayList;
import java.util.List;
import java.util.Optional;
import java.util.stream.Collectors;

@Service
public class CatService {
    private final CatDAO catDAO;
    private final FriendshipDAO friendshipDAO;

    @Autowired
    public CatService(CatDAO catDAO, FriendshipDAO friendshipDAO) {
        this.catDAO = catDAO;
        this.friendshipDAO = friendshipDAO;
    }

    public void addCat(CatDTO cat) {
        if (cat.getName() == null || cat.getName().isEmpty()) {
            throw new IllegalArgumentException("Cat's name cannot be null");
        }

        if (cat.getBirthDate() == null) {
            throw new IllegalArgumentException("Cat's date of birth cannot be null");
        }

        catDAO.save(convert(cat));
    }

    public static Cat convert(CatDTO cat) {
        return new Cat()
                .setName(cat.getName())
                .setBirthDate(cat.getBirthDate())
                .setBreed(cat.getBreed())
                .setColor(cat.getColor())
                .setOwner(OwnerService.convert(cat.getOwner()));
    }

    public static CatDTO convert(Cat cat) {
        CatDTO result = new CatDTO().setId(cat.getId())
                .setName(cat.getName())
                .setBirthDate(cat.getBirthDate())
                .setBreed(cat.getBreed())
                .setColor(cat.getColor());
        result.setFriendIds(cat.getFriends().stream()
                .map(Cat::getId)
                .collect(Collectors.toList()));
            result.setOwner(OwnerService.convert(cat.getOwner()));
        return result;
    }

    public CatFriendshipDTO convert(CatFriendship catFriendship) {
        return new CatFriendshipDTO()
                .setId(catFriendship.getId())
                .setCatId(catFriendship.getCatId())
                .setFriendId(catFriendship.getFriendId());
    }

    public CatFriendship convert(CatFriendshipDTO catFriendship) {
        return new CatFriendship()
                .setCatId(catFriendship.getCatId())
                .setFriendId(catFriendship.getFriendId());
    }

    public List<CatDTO> getAllCats() {
        List<Cat> cats = catDAO.findAll();
        return cats.stream()
                .map(CatService::convert)
                .collect(Collectors.toList());
    }

    public List<CatDTO> getBy(Long ownerId, String color, String breed) {
        Color color_param;
        if (color == null) {
            color_param = null;
        } else {
            color_param = Color.valueOf(color);
        }
        List<Cat> cats = catDAO.findByParameters(ownerId, breed, color_param);
        return cats.stream()
                .map(CatService::convert)
                .collect(Collectors.toList());
    }

    public CatDTO getById(Long id) {
        Optional<Cat> optionalCat = catDAO.findById(id);
        if (optionalCat.isPresent()) {
            return convert(optionalCat.get());
        } else {
            throw new IllegalArgumentException("Cat with id " + id + " is not found");
        }
    }

    public List<CatFriendshipDTO> addFriendship(Long id1, Long id2) {
        Optional<Cat> optionalCat1 = catDAO.findById(id1);
        Optional<Cat> optionalCat2 = catDAO.findById(id2);

        if (optionalCat1.isEmpty() || optionalCat2.isEmpty()) {
            throw new IllegalArgumentException("Cat not found");
        }

        Cat cat1 = optionalCat1.get();
        Cat cat2 = optionalCat2.get();
        if (cat1.getFriends().contains(cat2)) {
            throw new IllegalArgumentException("Cats already are friends");
        }
        List<CatFriendship> friendships = new ArrayList<>();
        friendships.add(friendshipDAO.save(new CatFriendship().setCatId(id1).setFriendId(id2)));
        friendships.add(friendshipDAO.save(new CatFriendship().setCatId(id2).setFriendId(id1)));

        return friendships.stream()
                .map(this::convert)
                .collect(Collectors.toList());
    }
}
