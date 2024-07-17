package com.stt0504;

import lombok.Getter;
import lombok.Setter;

import jakarta.persistence.*;

@Getter
@Setter
@Entity
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
