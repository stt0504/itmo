package com.stt0504.Entities;

import lombok.Getter;
import lombok.Setter;
import lombok.experimental.Accessors;

import jakarta.persistence.*;
import java.time.LocalDate;
import java.util.ArrayList;
import java.util.List;

@Getter
@Setter
@Entity
@Accessors(chain = true)
@Table(name = "cats")
public class Cat {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    @Column(name = "cat_id")
    private Long id;

    @Column(name = "name")
    private String name;

    @Column(name = "birth_date")
    private LocalDate birthDate;

    @Column(name = "breed")
    private String breed;

    @Column(name = "color")
    @Enumerated(EnumType.STRING)
    private Color color;

    @ManyToOne
    @JoinColumn(name = "owner_id")
    private Owner owner;

    @ManyToMany(fetch = FetchType.EAGER)
    @JoinTable(
            name = "cat_friendship",
            joinColumns = @JoinColumn(name = "cat_id"),
            inverseJoinColumns = @JoinColumn(name = "friend_id")
    )
    private List<Cat> friends = new ArrayList<>();
}
