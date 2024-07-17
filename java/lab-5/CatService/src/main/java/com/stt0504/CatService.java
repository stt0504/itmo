package com.stt0504;

import com.stt0504.Entities.Cat;
import com.stt0504.Entities.CatFriendship;
import com.stt0504.Entities.Color;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.kafka.annotation.KafkaListener;
import org.springframework.kafka.core.KafkaTemplate;
import org.springframework.stereotype.Service;

import java.util.ArrayList;
import java.util.List;
import java.util.Optional;
import java.util.stream.Collectors;

@Service
public class CatService {
    private final CatDAO catDAO;
    private final FriendshipDAO friendshipDAO;
    private final KafkaTemplate<String, Object> template;
    @Autowired
    public CatService(CatDAO catDAO, FriendshipDAO friendshipDAO, KafkaTemplate<String, Object> template) {
        this.catDAO = catDAO;
        this.friendshipDAO = friendshipDAO;
        this.template = template;
    }

    public Cat convert(CatDTO cat) {
        Cat result = new Cat()
                .setName(cat.getName())
                .setBreed(cat.getBreed())
                .setColor(cat.getColor());
        return result;
    }

    public CatDTO convert(Cat cat) {
        CatDTO result = new CatDTO().setId(cat.getId())
                .setName(cat.getName())
                .setBreed(cat.getBreed())
                .setColor(cat.getColor());
        result.setFriendIds(cat.getFriends().stream()
                .map(Cat::getId)
                .collect(Collectors.toList()));
        if (cat.getOwner() != null) {
            result.setOwnerId(cat.getOwner().getId());
        }
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

    @KafkaListener(topics = "add_cat", groupId = "cat_group")
    public void addCat(List<String> params) {
        String name = params.get(0);
        String breed = params.get(1);
        Color color = Color.valueOf(params.get(2));
        if (name == null || name.isEmpty()) {
            throw new IllegalArgumentException("Cat's name cannot be null");
        }
        CatDTO dto = new CatDTO().setName(name).setColor(color).setBreed(breed);
        CatDTO result = convert(catDAO.save(convert(dto)));
        template.send("send_added_cat", result);
    }

    @KafkaListener(topics = "get_all_cats", groupId = "cat_group")
    public List<CatDTO> getAllCats() {
        List<Cat> cats = catDAO.findAll();
        List<CatDTO> result = cats.stream()
                .map(this::convert)
                .collect(Collectors.toList());
        template.send("send_all_cats", result);
        return result;
    }

    @KafkaListener(topics = "get_cats_by", groupId = "cat_group")
    public List<CatDTO> getBy(List<String> filterDetails) {
        Long ownerId = Long.parseLong(filterDetails.get(0));
        Color color = Color.valueOf(filterDetails.get(1));
        String breed = filterDetails.get(2);
        List<Cat> cats = catDAO.findByParameters(ownerId, breed, color);
        List<CatDTO> result = cats.stream()
                .map(this::convert)
                .collect(Collectors.toList());
        template.send("send_cats_list", result);
        return result;
    }

    @KafkaListener(topics = "cat_get", groupId = "cat_group")
    public CatDTO getById(Long id) {
        Optional<Cat> optionalCat = catDAO.findById(id);
        CatDTO result;
        if (optionalCat.isPresent()) {
            result = convert(optionalCat.get());
            template.send("cat_found", result);
            return result;
        } else {
            throw new IllegalArgumentException("Cat with id " + id + " is not found");
        }
    }

    @KafkaListener(topics = "add_friendship", groupId = "cat_group")
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
