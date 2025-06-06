﻿#pragma once

#define GETTER(type, varName) \
UFUNCTION(BlueprintCallable) \
FORCEINLINE type Get##varName() const { return varName; }

#define GETTER_REF(type, varName) \
UFUNCTION(BlueprintCallable) \
FORCEINLINE type& Get##varName() { return varName; }

#define GETTER_EDITABLE(type, varName) \
UFUNCTION(BlueprintCallable) \
FORCEINLINE type Get##varName() { return varName; }

#define SETTER(type, varName) \
UFUNCTION(BlueprintCallable) \
FORCEINLINE void Set##varName(type val) { varName = val; }

#define GETTER_SETTER(type, varName) \
GETTER(type, varName) \
SETTER(type, varName)

#define GETTER_TEMPLATE(baseType, varName) \
template <typename T, std::enable_if_t<std::is_base_of_v<baseType, T>, int>  = 0> \
T* Get##varName() const { return varName ? Cast<T>(varName) : nullptr; }
