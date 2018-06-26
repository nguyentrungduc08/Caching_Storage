namespace cpp Task1

struct UserProfile {
  1: i32 uid,
  2: string name,
  3: i16 age,
  4: i8 gender	
}

typedef list<UserProfile> listUser
typedef i32 idcounter    

service UserStorage {
  i32 createUser(1: UserProfile user),
  UserProfile getUser(1: i32 uid),
  void editUser(1: i32 uid)
}
