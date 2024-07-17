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
    implementation(project(":Controller"))
    implementation(project(":Service"))
    implementation(project(":Dao"))
    implementation(project(":Entity"))
    implementation("org.hibernate:hibernate-core:6.0.0.Final")
    implementation("org.postgresql:postgresql:42.2.24")
    testImplementation("org.mockito:mockito-core:3.12.4")
    implementation("org.springframework.boot:spring-boot-starter")
    testImplementation("org.springframework.boot:spring-boot-starter-test")
    implementation("org.springframework.boot:spring-boot-starter-data-jpa")
}

tasks.test {
    useJUnitPlatform()
}