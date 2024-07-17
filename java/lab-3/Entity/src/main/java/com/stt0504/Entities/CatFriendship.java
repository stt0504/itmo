package com.stt0504.Entities;

import lombok.Getter;
import lombok.Setter;

import jakarta.persistence.*;
import lombok.experimental.Accessors;

@Getter
@Setter
@Entity
@Accessors(chain = true)
@Table(name = "cat_friendship")
public class CatFriendship {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    @Column(name = "id")
    private Long id;

    @Column(name = "cat_id")
    private Long catId;

    @Column(name = "friend_id")
    private Long friendId;
}
