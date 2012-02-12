#ifndef Shadows_Accessors_h
#define Shadows_Accessors_h

#define GET_SET_(type, name)\
public:\
inline void set_##name(const type& name) { name##_ = name; }; \
inline type name() { return name##_; };\

#define GET_DYN_SET_(type, name)\
public:\
void set_##name(const type& name); \
inline type name() { return name##_; };\

#define GET_(type, name)\
public:\
inline type name() { return name##_; };\

#endif
