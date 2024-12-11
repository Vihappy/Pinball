class CollisionListener : public b2ContactListener {
public:
    int* score;

    CollisionListener(int* scorePtr) : score(scorePtr) {}

    void BeginContact(b2Contact* contact) override {
        // Obtener los datos de usuario de los cuerpos involucrados en la colisión
        void* userDataA = reinterpret_cast<void*>(contact->GetFixtureA()->GetBody()->GetUserData().pointer);
        void* userDataB = reinterpret_cast<void*>(contact->GetFixtureB()->GetBody()->GetUserData().pointer);

        if (userDataA && userDataB) {
            std::string* tagA = static_cast<std::string*>(userDataA);
            std::string* tagB = static_cast<std::string*>(userDataB);

            if ((*tagA == "ball" && *tagB == "bumper") || (*tagA == "bumper" && *tagB == "ball")) {
                (*score)++;
                std::cout << "Score: " << *score << std::endl;
            }
        }
    }
};