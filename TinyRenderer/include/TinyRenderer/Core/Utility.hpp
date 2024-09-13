//
// Created by Sayama on 13/09/2024.
//

#pragma once

#define TR_BIND_MEMBER_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }
#define TR_BIND_FN(fn) [](auto&&... args) -> decltype(auto) { return fn(std::forward<decltype(args)>(args)...); }