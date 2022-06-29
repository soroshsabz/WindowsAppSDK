﻿#include "pch.h"
#include "Button.h"
#include "Microsoft.Windows.AppNotifications.Builder.Button.g.cpp"

namespace winrt::Microsoft::Windows::AppNotifications::Builder::implementation
{
    Button::Button(winrt::hstring const& content) : m_content(content) { };

    winrt::Microsoft::Windows::AppNotifications::Builder::Button Button::AddArgument(winrt::hstring const& key, winrt::hstring const& value)
    {
        m_arguments.Insert(key, value);
        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::Button Button::SetIconUri(winrt::Windows::Foundation::Uri iconUri)
    {
        m_iconUri = iconUri;
        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::Button Button::UseProtocolActivation(winrt::Windows::Foundation::Uri protocolUri)
    {
        m_protocolUri = protocolUri;
        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::Button Button::SetToolTip(winrt::hstring const& toolTip)
    {
        m_toolTip = toolTip;
        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::Button Button::SetInputId(winrt::hstring const& inputId)
    {
        m_inputId = inputId;
        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::Button Button::UseContextMenuPlacement()
    {
        m_useContextMenuPlacement = true;
        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::Button Button::SetButtonStyle(ButtonStyle const& buttonStyle)
    {
        m_buttonStyle = buttonStyle;
        return *this;
    }

    winrt::hstring Button::GetXml()
    {
        winrt::hstring xml{ L"<action content=" + m_content + L" arguments="};
        for (auto pair : m_arguments)
        {
            xml = xml + pair.Key() + L"&" + pair.Value() + L";";
        }

        if (m_useContextMenuPlacement)
        {
            xml = xml + LR"( placement="contextMenu")";
        }

        if (m_iconUri)
        {
            xml = xml + L" imageUri=" + m_iconUri.ToString();
        }

        if (m_protocolUri)
        {
            xml = xml + LR"( activationType="protocol" protocolActivationTargetApplicationPfn=)" + m_protocolUri.ToString();
        }

        if (!m_inputId.empty())
        {
            xml = xml + L" hint-inputId=" + m_inputId;
        }

        if (m_buttonStyle == ButtonStyle::Success)
        {
            xml = xml + LR"( hint-buttonStyle="success")";
        }
        else if (m_buttonStyle == ButtonStyle::Success)
        {
            xml = xml + LR"( hint-buttonStyle="critical")";
        }

        if (!m_toolTip.empty())
        {
            xml = xml + L" hint-toolTip=" + m_toolTip;
        }

        xml = xml + L" />";
        return xml;
    }
}
