package com.stt0504;

import java.util.List;
import java.util.stream.Collectors;

public class CatService {
    private final CatDAO catDAO;
    private final OwnerDAO ownerDAO;

    private final ColorConverter colorConverter;

    public CatService(CatDAO catDAO, OwnerDAO ownerDAO, ColorConverter colorConverter) {
        this.catDAO = catDAO;
        this.ownerDAO = ownerDAO;
        this.colorConverter = colorConverter;
    }

    public CatDTO addCat(CatDTO cat) {
        if (cat.getName() == null || cat.getName().isEmpty()) {
            throw new IllegalArgumentException("Cat's name cannot be null");
        }

        if (cat.getBirthDate() == null) {
            throw new IllegalArgumentException("Cat's date of birth cannot be null");
        }

        if (ownerDAO.getOwnerById(cat.getOwnerId()) == null) {
            throw new IllegalArgumentException("No such owner");
        }

        return convert(catDAO.addCat(convert(cat)));
    }

    public Cat convert(CatDTO cat) {
        Cat result = new Cat().setName(cat.getName())
                .setBirthDate(cat.getBirthDate())
                .setBreed(cat.getBreed())
                .setColor(colorConverter.convertToEntity(cat.getColor()));
        if (cat.getOwnerId() != null) {
            result.setOwner(ownerDAO.getOwnerById(cat.getOwnerId()));
        }
        return result;
    }

    public CatDTO convert(Cat cat) {
        CatDTO result = new CatDTO().setId(cat.getId())
                .setName(cat.getName())
                .setBirthDate(cat.getBirthDate())
                .setBreed(cat.getBreed())
                .setColor(colorConverter.convertToDTO(cat.getColor()));
        result.setFriendIds(cat.getFriends().stream()
                .map(Cat::getId)
                .collect(Collectors.toList()));
        if (cat.getOwner() != null) {
            result.setOwnerId(cat.getOwner().getId());
        }
        return result;
    }

    public List<CatDTO> getAllCats() {
        List<Cat> cats = catDAO.getAllCats();
        return cats.stream()
                .map(this::convert)
                .collect(Collectors.toList());
    }

    public CatDTO getCatById(Long id) {
        return convert(catDAO.getCatById(id));
    }

    public void addFriendship(Long id1, Long id2) {
        Cat cat1 = catDAO.getCatById(id1);
        Cat cat2 = catDAO.getCatById(id2);
        if (cat1.getFriends().contains(cat2)) {
            throw new IllegalArgumentException("Cats already are friends");
        }
        catDAO.addFriendship(id1, id2);
    }

    public List<CatDTO> getFriends(CatDTO cat) {
        List<Long> friendIds = cat.getFriendIds();
        return friendIds.stream()
                .map(catId -> convert(catDAO.getCatById(catId)))
                .collect(Collectors.toList());
    }

    public List<CatDTO> getCats(OwnerDTO owner) {
        List<Long> catIds = owner.getCatIds();
        return catIds.stream()
                .map(catId -> convert(catDAO.getCatById(catId)))
                .collect(Collectors.toList());
    }
}
