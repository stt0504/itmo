plugins {
    id("java")
    id("org.springframework.boot") version "3.2.4"
    id("io.spring.dependency-management") version "1.1.4"
}

group = "com.stt0504"
version = "1.0-SNAPSHOT"

repositories {
    mavenCentral()
}

dependencies {
    testImplementation(platform("org.junit:junit-bom:5.9.1"))
    testImplementation("org.junit.jupiter:junit-jupiter")
    implementation("org.hibernate:hibernate-core:6.4.4.Final")
    compileOnly("org.projectlombok:lombok:1.18.20")
    annotationProcessor("org.projectlombok:lombok:1.18.20")
    implementation(project(":Entity"))
    implementation(project(":DTO"))
    implementation("org.postgresql:postgresql:42.2.24")
    implementation("org.springframework.boot:spring-boot-starter")
    implementation("org.springframework.boot:spring-boot-starter-data-jpa")
    testImplementation("org.springframework.boot:spring-boot-starter-test")
    implementation("jakarta.persistence:jakarta.persistence-api:3.1.0")
    implementation ("org.springframework.kafka:spring-kafka")
    implementation ("com.fasterxml.jackson.core:jackson-databind:2.13.0")
    implementation ("com.fasterxml.jackson.datatype:jackson-datatype-jsr310:2.13.0")
}

tasks.test {
    useJUnitPlatform()
}