// Copyright (c) Microsoft Corporation.
// Licensed under the MIT license.

#pragma once

#include "cppwinrt_utils.h"
#include "VisualBellLight.g.h"
#include "CursorLight.g.h"

#define CREATE_XAML_LIGHT(name)                                                                                                                 \
public:                                                                                                                                         \
    name()                                                                                                                                      \
    {                                                                                                                                           \
        _InitializeProperties();                                                                                                                \
    }                                                                                                                                           \
                                                                                                                                                \
    winrt::hstring GetId()                                                                                                                      \
    {                                                                                                                                           \
        return name::GetIdStatic();                                                                                                             \
    }                                                                                                                                           \
                                                                                                                                                \
    static Windows::UI::Xaml::DependencyProperty IsTargetProperty()                                                                             \
    {                                                                                                                                           \
        return _IsTargetProperty;                                                                                                               \
    }                                                                                                                                           \
                                                                                                                                                \
    static bool GetIsTarget(Windows::UI::Xaml::DependencyObject const& target)                                                                  \
    {                                                                                                                                           \
        return winrt::unbox_value<bool>(target.GetValue(_IsTargetProperty));                                                                    \
    }                                                                                                                                           \
                                                                                                                                                \
    static void SetIsTarget(Windows::UI::Xaml::DependencyObject const& target, bool value)                                                      \
    {                                                                                                                                           \
        target.SetValue(_IsTargetProperty, winrt::box_value(value));                                                                            \
    }                                                                                                                                           \
                                                                                                                                                \
    void OnDisconnected(Windows::UI::Xaml::UIElement const& /*oldElement*/)                                                                     \
    {                                                                                                                                           \
        if (CompositionLight())                                                                                                                 \
        {                                                                                                                                       \
            CompositionLight(nullptr);                                                                                                          \
        }                                                                                                                                       \
    }                                                                                                                                           \
                                                                                                                                                \
    static void OnIsTargetChanged(Windows::UI::Xaml::DependencyObject const& d, Windows::UI::Xaml::DependencyPropertyChangedEventArgs const& e) \
    {                                                                                                                                           \
        const auto uielem{ d.try_as<Windows::UI::Xaml::UIElement>() };                                                                          \
        const auto brush{ d.try_as<Windows::UI::Xaml::Media::Brush>() };                                                                        \
                                                                                                                                                \
        if (!uielem && !brush)                                                                                                                  \
        {                                                                                                                                       \
            /* terminate early*/                                                                                                                \
            return;                                                                                                                             \
        }                                                                                                                                       \
                                                                                                                                                \
        const auto isAdding = winrt::unbox_value<bool>(e.NewValue());                                                                           \
        const auto id = GetIdStatic();                                                                                                          \
                                                                                                                                                \
        if (isAdding)                                                                                                                           \
        {                                                                                                                                       \
            if (uielem)                                                                                                                         \
            {                                                                                                                                   \
                Windows::UI::Xaml::Media::XamlLight::AddTargetElement(id, uielem);                                                              \
            }                                                                                                                                   \
            else                                                                                                                                \
            {                                                                                                                                   \
                Windows::UI::Xaml::Media::XamlLight::AddTargetBrush(id, brush);                                                                 \
            }                                                                                                                                   \
        }                                                                                                                                       \
        else                                                                                                                                    \
        {                                                                                                                                       \
            if (uielem)                                                                                                                         \
            {                                                                                                                                   \
                Windows::UI::Xaml::Media::XamlLight::RemoveTargetElement(id, uielem);                                                           \
            }                                                                                                                                   \
            else                                                                                                                                \
            {                                                                                                                                   \
                Windows::UI::Xaml::Media::XamlLight::RemoveTargetBrush(id, brush);                                                              \
            }                                                                                                                                   \
        }                                                                                                                                       \
    }                                                                                                                                           \
                                                                                                                                                \
    inline static winrt::hstring GetIdStatic()                                                                                                  \
    {                                                                                                                                           \
        /* This specifies the unique name of the light. In most cases you should use the type's full name. */                                   \
        return winrt::xaml_typename<winrt::Microsoft::Terminal::Control::name>().Name;                                                          \
    }

namespace winrt::Microsoft::Terminal::Control::implementation
{
    struct VisualBellLight : VisualBellLightT<VisualBellLight>
    {
        CREATE_XAML_LIGHT(VisualBellLight);
        void OnConnected(Windows::UI::Xaml::UIElement const& newElement);

    private:
        static void _InitializeProperties();
        static Windows::UI::Xaml::DependencyProperty _IsTargetProperty;
    };

    struct CursorLight : CursorLightT<CursorLight>
    {
        CREATE_XAML_LIGHT(CursorLight);
        void ChangeLocation(float xCoord, float yCoord);
        void OnConnected(Windows::UI::Xaml::UIElement const& newElement);

    private:
        static void _InitializeProperties();
        static Windows::UI::Xaml::DependencyProperty _IsTargetProperty;
    };
}

namespace winrt::Microsoft::Terminal::Control::factory_implementation
{
    BASIC_FACTORY(VisualBellLight);
    BASIC_FACTORY(CursorLight);
}
