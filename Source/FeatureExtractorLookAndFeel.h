/*
  ==============================================================================

    FeatureExtractorLookAndFeel.h
    Created: 10 Feb 2016 8:00:52pm
    Author:  Sean

  ==============================================================================
*/

#ifndef FEATUREEXTRACTORLOOKANDFEEL_H_INCLUDED
#define FEATUREEXTRACTORLOOKANDFEEL_H_INCLUDED

//==============================================================================
/* Look and feel and layout functions
*/
class FeatureExtractorLookAndFeel : public LookAndFeel_V3
{
public:
    FeatureExtractorLookAndFeel() {}

    static float  getAudioDisplayHeightRatio()               noexcept { return 0.2f; }
    static float  getFeatureVisualiserComponentHeightRatio() noexcept { return 0.4f; }
    static float  getSettingsHeightRatio()                   noexcept { return 0.4f; }
    static float  getDeviceSettingsComboBoxWidthRatio()      noexcept { return 0.6f; }
    static int    getMaxDeviceSettingsListBoxHeight()        noexcept { return 100; }
    static int    getDeviceSettingsItemHeight()              noexcept { return 24; }
    static int    getOSCItemHeight()                         noexcept { return 18; }
    static int    getInnerComponentSpacing()                 noexcept { return 6; }
    static int    getComponentInset()                        noexcept { return 7; }
    static int    getFeatureVisualiserTextHeight()           noexcept { return 10; }
    static int    getFeatureVisualiserGraphicWidth()         noexcept { return 2; }
    static int    getTriggerFeatureVisualiserSquareSize()    noexcept { return 15; } 
    static int    getOSCSettingsWidth()                      noexcept { return 200; }
    static int    getOSCSettingsHeight()                     noexcept { return 150; }
    static int    getAudioTransportControlsWidth()           noexcept { return 200; }
    static int    getAudioTransportControlsHeight()          noexcept { return 50; }
    static int    getAudioSourceTypeSelectorWidth()          noexcept { return 200; }
    static int    getAudioSourceTypeSelectorHeight()         noexcept { return 20; }
    static int    getFeatureVisualiserTextGraphicMargin()    noexcept { return 15; }
    static int    getVerticalMargin()                        noexcept { return 50; }
    static int    getHorizontalMargin()                      noexcept { return 30; }
    static int    getAnimationRateHz ()                      noexcept { return 60; }
    static int    getSliderHeight()                          noexcept { return 20; }
    static int    getAnalyserTrackHeight()                   noexcept { return 200; }
    static float  getCornerSize()                            noexcept { return 4.0f; }
    static float  getLineThickness()                         noexcept { return 1.0f; }
    static Colour getTextColour()                            noexcept { return Colours::white; }
    static Colour getControlBackgroundColour()               noexcept { return Colours::green; }
    static Colour getForegroundInteractiveColour()           noexcept { return Colours::lightgreen; }
    static Colour getBackgroundColour()                      noexcept { return Colours::black; }
    static Colour getSelectedColour()                        noexcept { return Colours::green; }
    static Colour getUnselectedColour()                      noexcept { return Colours::grey; }
    static Colour getAudioTransportButtonForegroundColour()  noexcept { return Colours::black; }
    static Colour getBufferBackgroundColour()                noexcept { return Colours::black; }
    static Colour getBufferForegroundColour()                noexcept { return Colours::white; }

    static void paintFeatureVisualiser (Graphics& g, float value, Rectangle<int> visualiserBounds)
    {
        g.setColour            (Colours::white);
        g.fillRoundedRectangle (visualiserBounds.toFloat(), getCornerSize());
        int height =           (int) (visualiserBounds.getHeight() * value);
        g.setColour            (Colours::green);
        g.fillRoundedRectangle (visualiserBounds.removeFromBottom (height).toFloat(), getCornerSize());
    }

    static void paintTriggerFeatureVisualiser (Graphics& g, Rectangle<int> visualiserBounds, float opacity)
    {
        g.setColour (Colours::green.withAlpha (opacity));
        g.fillRoundedRectangle (visualiserBounds.toFloat(), getCornerSize());
        g.setColour (Colours::white);
        g.drawRoundedRectangle (visualiserBounds.toFloat(), getCornerSize(), getLineThickness());
    }

    void drawLabel (Graphics& g, Label& label) override
    {
        g.fillAll (label.findColour (Label::backgroundColourId));

        if (! label.isBeingEdited())
        {
            const float alpha = label.isEnabled() ? 1.0f : 0.5f;
            const Font font (getLabelFont (label));

            g.setColour (getTextColour().withMultipliedAlpha (alpha));
            g.setFont (font);

            Rectangle<int> textArea (label.getBorderSize().subtractedFrom (label.getLocalBounds()));

            g.drawFittedText (label.getText(), textArea, label.getJustificationType(),
                              jmax (1, (int) (textArea.getHeight() / font.getHeight())),
                              label.getMinimumHorizontalScale());

            g.setColour (label.findColour (Label::outlineColourId).withMultipliedAlpha (alpha));
        }
        else if (label.isEnabled())
        {
            g.setColour (label.findColour (Label::outlineColourId));
        }

        g.drawRect (label.getLocalBounds());
    }

    void drawComboBox (Graphics& g, int /*width*/, int /*height*/, bool /*isButtonDown*/,
                                   int buttonX, int buttonY, int buttonW, int buttonH, ComboBox& box) override
    {
        g.setColour (getControlBackgroundColour());
        g.fillRoundedRectangle (box.getLocalBounds().toFloat(), getCornerSize());

        const Colour buttonColour (box.findColour (ComboBox::buttonColourId));

        const float arrowX = 0.3f;
        const float arrowH = 0.2f;

        Path p;
        p.addTriangle (buttonX + buttonW * 0.5f,            buttonY + buttonH * (0.45f - arrowH),
                       buttonX + buttonW * (1.0f - arrowX), buttonY + buttonH * 0.45f,
                       buttonX + buttonW * arrowX,          buttonY + buttonH * 0.45f);

        p.addTriangle (buttonX + buttonW * 0.5f,            buttonY + buttonH * (0.55f + arrowH),
                       buttonX + buttonW * (1.0f - arrowX), buttonY + buttonH * 0.55f,
                       buttonX + buttonW * arrowX,          buttonY + buttonH * 0.55f);

        g.setColour (box.findColour (ComboBox::arrowColourId).withMultipliedAlpha (box.isEnabled() ? 1.0f : 0.3f));
        g.fillPath (p);
    }

    void drawPopupMenuBackground (Graphics& g, int width, int height) override
    {
        g.fillAll (Colours::black);
        g.setColour (getControlBackgroundColour());
        g.fillRoundedRectangle (0, 0, (float) width, (float) height, getCornerSize());
        ignoreUnused (width, height);
    }

    void drawPopupMenuItem (Graphics& g, const Rectangle<int>& area,
                                         bool isSeparator,   bool isActive,
                                         bool isHighlighted, bool isTicked,
                                         bool hasSubMenu,    const String& text,
                                         const String& shortcutKeyText,
                                         const Drawable* icon, const Colour* textColourToUse) override
    {
        if (isSeparator)
        {
            Rectangle<int> r (area.reduced (5, 0));
            r.removeFromTop (r.getHeight() / 2 - 1);

            g.setColour (Colour (0x33000000));
            g.fillRect (r.removeFromTop (1));

            g.setColour (Colour (0x66ffffff));
            g.fillRect (r.removeFromTop (1));
        }
        else
        {
            Colour textColour (findColour (PopupMenu::textColourId));

            if (textColourToUse != nullptr)
                textColour = *textColourToUse;

            Rectangle<int> r (area.reduced (1));

            if (isHighlighted)
            {
                g.setColour (findColour (PopupMenu::highlightedBackgroundColourId));
                g.fillRoundedRectangle (r.toFloat(), getCornerSize());

                g.setColour (findColour (PopupMenu::highlightedTextColourId));
            }
            else
            {
                g.setColour (textColour);
            }

            if (! isActive)
                g.setOpacity (0.3f);

            Font font (getPopupMenuFont());

            const float maxFontHeight = area.getHeight() / 1.3f;

            if (font.getHeight() > maxFontHeight)
                font.setHeight (maxFontHeight);

            g.setFont (font);

            Rectangle<float> iconArea (r.removeFromLeft ((r.getHeight() * 5) / 4).reduced (3).toFloat());

            if (icon != nullptr)
            {
                icon->drawWithin (g, iconArea, RectanglePlacement::centred | RectanglePlacement::onlyReduceInSize, 1.0f);
            }
            else if (isTicked)
            {
                const Path tick (getTickShape (1.0f));
                g.fillPath (tick, tick.getTransformToScaleToFit (iconArea, true));
            }

            if (hasSubMenu)
            {
                const float arrowH = 0.6f * getPopupMenuFont().getAscent();

                const float x = (float) r.removeFromRight ((int) arrowH).getX();
                const float halfH = (float) r.getCentreY();

                Path p;
                p.addTriangle (x, halfH - arrowH * 0.5f,
                               x, halfH + arrowH * 0.5f,
                               x + arrowH * 0.6f, halfH);

                g.fillPath (p);
            }

            r.removeFromRight (3);
            g.drawFittedText (text, r, Justification::centredLeft, 1);

            if (shortcutKeyText.isNotEmpty())
            {
                Font f2 (font);
                f2.setHeight (f2.getHeight() * 0.75f);
                f2.setHorizontalScale (0.95f);
                g.setFont (f2);

                g.drawText (shortcutKeyText, r, Justification::centredRight, true);
            }
        }
    }

    enum eAudioTransportButtonType
    {
        enPlay = 0,
        enPause,
        enRestart,
        enStop
    };

    static void drawAudioTransportButton (Graphics& g, eAudioTransportButtonType t, Rectangle<int> bounds, Button& button)
    {
        Colour baseColour (getControlBackgroundColour().withMultipliedSaturation (button.hasKeyboardFocus (true) ? 1.3f : 0.9f)
                                                       .withMultipliedAlpha (button.isEnabled() ? 0.9f : 0.5f));

        if (button.isMouseButtonDown() || button.isMouseOver())
            baseColour = baseColour.contrasting (button.isMouseButtonDown() ? 0.2f : 0.1f);

        g.setColour (baseColour);
        g.fillRoundedRectangle (button.getLocalBounds().toFloat(), getCornerSize());

        g.setColour (getAudioTransportButtonForegroundColour());
        const auto b = bounds.withSizeKeepingCentre (30, 30).toFloat();
        const auto w = b.getWidth();
        const auto h = b.getHeight();
        const auto quarterWidth = b.getX() + w / 4.0f;
        const auto threeQuarterWidth = b.getRight() - (w / 4.0f);
        switch (t)
        {
        case enPlay:
            g.drawLine (quarterWidth,      b.getY(),       threeQuarterWidth, b.getCentreY());
            g.drawLine (threeQuarterWidth, b.getCentreY(), quarterWidth,      b.getBottom());
            break;
        case enPause:
            g.drawLine (quarterWidth,      b.getY(), quarterWidth,      b.getBottom());
            g.drawLine (threeQuarterWidth, b.getY(), threeQuarterWidth, b.getBottom());
            break;
        case enRestart:
            g.drawLine (b.getX(), b.getCentreY(), quarterWidth, b.getY());
            g.drawLine (b.getX(), b.getCentreY(), quarterWidth, b.getBottom());
            g.drawLine (threeQuarterWidth, b.getCentreY(), b.getRight(), b.getY());
            g.drawLine (threeQuarterWidth, b.getCentreY(), b.getRight(), b.getBottom());
            break;
        case enStop:
            g.drawRoundedRectangle (b.toFloat(), getCornerSize(), getLineThickness());
            break;
        default:
            break;
        }
    }

    void drawButtonBackground (Graphics& g, Button& button, const Colour& /*backgroundColour*/,
                                           bool isMouseOverButton, bool isButtonDown) override
    {
        Colour baseColour (getControlBackgroundColour().withMultipliedSaturation (button.hasKeyboardFocus (true) ? 1.3f : 0.9f)
                                                       .withMultipliedAlpha (button.isEnabled() ? 0.9f : 0.5f));

        if (isButtonDown || isMouseOverButton)
            baseColour = baseColour.contrasting (isButtonDown ? 0.2f : 0.1f);

        g.setColour (baseColour);
        g.fillRoundedRectangle (button.getLocalBounds().toFloat(), getCornerSize());
    }

    void drawTextEditorOutline (Graphics& g, int /*width*/, int /*height*/, TextEditor& textEditor) override
    {
        if (textEditor.isEnabled())
        {
            g.setColour (getControlBackgroundColour());
            g.drawRoundedRectangle (textEditor.getLocalBounds().toFloat(), getCornerSize(), getLineThickness());
        }
    }

    void fillTextEditorBackground (Graphics& g, int /*width*/, int /*height*/, TextEditor& textEditor)
    {
        g.setColour (getForegroundInteractiveColour());
        g.fillRoundedRectangle (textEditor.getLocalBounds().toFloat(), getCornerSize());
    }

    void drawScrollbar (Graphics& g, ScrollBar& scrollbar, int x, int y, int width, int height,
                        bool isScrollbarVertical, int thumbStartPosition, int thumbSize, bool isMouseOver, bool isMouseDown)
    {
        g.fillAll   (FeatureExtractorLookAndFeel::getBackgroundColour());
        g.setColour (FeatureExtractorLookAndFeel::getControlBackgroundColour());
        g.fillRoundedRectangle (scrollbar.getLocalBounds().toFloat(), FeatureExtractorLookAndFeel::getCornerSize());
        Path thumbPath;

        if (thumbSize > 0)
        {
            const float thumbIndent = (isScrollbarVertical ? width : height) * 0.25f;
            const float thumbIndentx2 = thumbIndent * 2.0f;

            if (isScrollbarVertical)
                thumbPath.addRoundedRectangle (x + thumbIndent, thumbStartPosition + thumbIndent,
                                               width - thumbIndentx2, thumbSize - thumbIndentx2, (width - thumbIndentx2) * 0.5f);
            else
                thumbPath.addRoundedRectangle (thumbStartPosition + thumbIndent, y + thumbIndent,
                                               thumbSize - thumbIndentx2, height - thumbIndentx2, (height - thumbIndentx2) * 0.5f);
        }

        Colour thumbCol (FeatureExtractorLookAndFeel::getForegroundInteractiveColour());

        if (isMouseOver || isMouseDown)
            thumbCol = thumbCol.withMultipliedAlpha (2.0f);

        g.setColour (thumbCol);
        g.fillPath (thumbPath);

        g.setColour (thumbCol.contrasting ((isMouseOver  || isMouseDown) ? 0.2f : 0.1f));
        g.strokePath (thumbPath, PathStrokeType (1.0f));
    }

    void drawTickBox (Graphics& g, Component& /*component*/,
                      float x, float y, float w, float h,
                      const bool ticked,
                      const bool /*isEnabled*/,
                      const bool /*isMouseOverButton*/,
                      const bool /*isButtonDown*/)
    {
        g.setColour (ticked ? getSelectedColour() : getUnselectedColour());
        if (ticked)
            g.fillEllipse (x, y, w, h);
        else
            g.drawEllipse (x, y, w, h, getLineThickness());
    }

    //================================================================================
    // Buffer drawing functions
    //================================================================================

    static void drawBuffer (Graphics& g, Rectangle<float> bounds, AudioSampleBuffer buffer)
    {
        const int numChannels = buffer.getNumChannels();
        const int numSamplesToDraw = buffer.getNumSamples();
        const int startSampleToDraw = 0;
        jassert (numSamplesToDraw <= buffer.getNumSamples() && startSampleToDraw + numSamplesToDraw <= buffer.getNumSamples());

        g.setColour (FeatureExtractorLookAndFeel::getBufferBackgroundColour());
        g.fillRect  (bounds);

        const auto channelHeight   = bounds.getHeight() / numChannels;
        const auto binWidth        = bounds.getWidth()  / (float) numSamplesToDraw;
        const auto visualAmplifier = 1.0f;
        RectangleList<float> bins;
        for (int channel = 0; channel < numChannels; channel++)
        {
            auto channelBounds = bounds.removeFromTop (channelHeight);
            
            for (int s = startSampleToDraw; s < numSamplesToDraw; s++)
            {
                const auto sampleValue = buffer.getSample (channel, s) * visualAmplifier; 
                const auto binBounds    = channelBounds.removeFromLeft (binWidth).removeFromBottom (sampleValue * channelHeight); 
                bins.add (binBounds);
            }
        }
        g.setColour (FeatureExtractorLookAndFeel::getBufferForegroundColour());
        g.fillRectList (bins);
    }

    static void drawBipolarBuffer (Graphics& g, Rectangle<float> bounds, AudioSampleBuffer buffer)
    {
        const int numChannels = buffer.getNumChannels();
        const int numSamplesToDraw = buffer.getNumSamples();
        const int startSampleToDraw = 0;
        jassert (numSamplesToDraw  <= buffer.getNumSamples() && startSampleToDraw + numSamplesToDraw <= buffer.getNumSamples());

        g.setColour (FeatureExtractorLookAndFeel::getBufferBackgroundColour());
        g.fillRect  (bounds);

        const auto channelHeight   = bounds.getHeight() / numChannels;
        const auto binWidth        = bounds.getWidth() / (float) numSamplesToDraw;
        const auto visualAmplifier = 1.0f;
        RectangleList<float> samples;
        for (int channel = 0; channel < numChannels; channel++)
        {
            auto channelBounds = bounds.removeFromTop (channelHeight);

            for (int s = startSampleToDraw; s < numSamplesToDraw; s++)
            {
                auto sampleBounds = channelBounds.removeFromLeft (binWidth);
                const auto sampleValue = buffer.getSample (channel, s) * visualAmplifier; 

                if (sampleValue >= 0.0f)
                    samples.add (sampleBounds.removeFromTop (channelHeight / 2.0f).removeFromBottom (sampleValue * channelHeight));
                else
                    samples.add (sampleBounds.removeFromBottom (channelHeight / 2.0f).removeFromTop ((float) (abs ((double) sampleValue)) * channelHeight));
            }
        }
        g.setColour (FeatureExtractorLookAndFeel::getBufferForegroundColour());
        g.fillRectList (samples);
    }

    static void drawPeakPoint (Graphics& g, Rectangle<float> bounds, Point<float> peakPoint)
    {
        const float peakX =      peakPoint.getX() * bounds.getWidth();
        const float zeroLine =   bounds.getHeight() * 0.5f;
        const float poleHeight = bounds.getHeight() * 0.5f;
        const float peakY =      zeroLine - peakPoint.getY() * poleHeight;
        g.setColour (Colours::red);
        g.fillEllipse (peakX, peakY, 3.0f, 3.0f);
    }
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FeatureExtractorLookAndFeel)
};



#endif  // FEATUREEXTRACTORLOOKANDFEEL_H_INCLUDED
