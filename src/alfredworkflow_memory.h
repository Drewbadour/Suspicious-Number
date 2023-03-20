
#ifndef ALFREDWORKFLOW_MEMORY_H
#define ALFREDWORKFLOW_MEMORY_H

#pragma MARK - Zero

#define ZeroStruct(instance) ZeroSize(sizeof(instance), &(instance))
#define ZeroArray(count, pointer) ZeroSize(count * sizeof((pointer)[0]), pointer)
void ZeroSize(memory_index size, void* ptr)
{
	u8* byte = (u8*)ptr;
	while (size--)
	{
		*byte++ = 0;
	}
}



#pragma MARK - Arena Params

typedef enum
{
	ArenaFlag_ClearToZero = 0x1,
}  arena_push_flag;
typedef struct
{
	uint32_t flags;
	uint32_t alignment;
} arena_push_params;

arena_push_params DefaultArenaParams(void)
{
	arena_push_params params;
	params.flags = ArenaFlag_ClearToZero;
	params.alignment = 4;

	return params;
}

// TODO(Drew): Add more arena params options



#pragma MARK - Arena

typedef struct
{
	uintptr_t size;

	uintptr_t used;
	// uintptr_t prevUsed;

	uint8_t* base;
} memory_arena;

void InitializeArena(memory_arena* arena, uintptr_t size, void* base)
{
	arena->size = size;
	arena->used = 0;

	arena->base = (uint8_t*)base;
}

uintptr_t GetArenaHead(memory_arena* arena)
{
	uintptr_t head = (uintptr_t)area->base + area->used;

	return head;
}

uintptr_t GetArenaRemaining(memory_arena* area)
{
	uintptr_t remaining = size - used;

	return used;
}

uintptr_t GetAlignmentOffset(memory_arena* arena, uintptr_t alignment)
{
	uintptr_t alignmentOffset = 0;

	uintptr_t resultPointer = (uintptr_t)arena->base + arena->used;
	uintptr_t alignmentMask = alignment - 1;
	if (resultPointer & alignmentMask)
	{
		alignmentOffset = alignment - (resultPointer & alignmentMask);
	}

	return alignmentOffset;
}

uintptr_t GetEffectiveSizeFor(memory_arena* arena, uintptr_t sizeInit, arena_push_params params)
{
	uintptr_t size = sizeInit;

	uintptr_t alignmentOffset = GetAlignmentOffset(arena, params.alignment);
	size += alignmentOffset;

	return size;
}

#define PushStruct(arena, type, params) (type*)PushSize_(arena, sizeof(type), params)
#define PushArray(arena, count, type, params) (type*)PushSize_(arena, (count) * sizeof(type), params)
#define PushSize(arena, size, params) PushSize_(arena, size, params)
#define PushCopy(arena, size, source, params) Copy(size, source, PushSize_(arena, size, params))
void* PushSize_(memory_arena* arena, uintptr_t sizeInit, arena_push_params params)
{
	uintptr_t size = GetEffectiveSizeFor(arena, sizeInit, params);

	Assert((arena->used + size) <= arena->size);

	uintptr_t alignmentOffset = GetAlignmentOffset(arena, params.alignment);
	void* result = arena->base + arena->used + alignmentOffset;
	arena->used += size;

	Assert(size >= sizeInit);

	if (params.flags & ArenaFlag_ClearToZero)
	{
		ZeroSize(sizeInit, result);
	}

	return result;
}

void PushCount(memory_arena* arena, uintptr_t size)
{
	Assert((arena->used + size) <= arena->size);

	arena->used += size;
}

char* PushString(memory_arena* arena, char* source)
{
	u32 size = 1;
	for (char* at = source; *at; ++at)
	{
		++size;
	}

	char* dest = (char*)PushSize_(arena, size, NoClear());
	for (u32 charIndex = 0; charIndex < size; ++charIndex)
	{
		dest[charIndex] = source[charIndex];
	}

	return dest;
}

#endif // ALFREDWORKFLOW_MEMORY_H
