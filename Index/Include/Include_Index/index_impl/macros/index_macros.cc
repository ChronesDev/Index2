#define var auto

#define global inline

#define stackalloc(type, length) (Index::Span<type>((type*)_malloca(length * sizeof(type)), length))

#define cat inline struct

#define elif else if

#define fun auto