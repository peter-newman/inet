//
// Copyright (C) OpenSim Ltd.
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program; if not, see <http://www.gnu.org/licenses/>.
//

#include "inet/common/ModuleAccess.h"
#include "inet/visualizer/physicallayer/RadioCanvasVisualizer.h"

namespace inet {

namespace visualizer {

using namespace inet::physicallayer;

Define_Module(RadioCanvasVisualizer);

RadioCanvasVisualizer::RadioCanvasVisualization::RadioCanvasVisualization(NetworkNodeCanvasVisualization *networkNodeVisualization, IndexedImageFigure *radioModeFigure, IndexedImageFigure *receptionStateFigure, IndexedImageFigure *transmissionStateFigure, cPolygonFigure *antennaLobeFigure, const int radioModuleId) :
    RadioVisualization(radioModuleId),
    networkNodeVisualization(networkNodeVisualization),
    radioModeFigure(radioModeFigure),
    receptionStateFigure(receptionStateFigure),
    transmissionStateFigure(transmissionStateFigure),
    antennaLobeFigure(antennaLobeFigure)
{
}

RadioCanvasVisualizer::RadioCanvasVisualization::~RadioCanvasVisualization()
{
    delete radioModeFigure;
}

void RadioCanvasVisualizer::initialize(int stage)
{
    RadioVisualizerBase::initialize(stage);
    if (!hasGUI()) return;
    if (stage == INITSTAGE_LOCAL) {
        zIndex = par("zIndex");
        networkNodeVisualizer = getModuleFromPar<NetworkNodeCanvasVisualizer>(par("networkNodeVisualizerModule"), this);
    }
}

RadioVisualizerBase::RadioVisualization *RadioCanvasVisualizer::createRadioVisualization(const IRadio *radio) const
{
    auto module = check_and_cast<const cModule *>(radio);
    // TODO: use RadioFigure?
    auto radioModeFigure = new IndexedImageFigure("radioMode");
    radioModeFigure->setTags((std::string("radioMode ") + tags).c_str());
    radioModeFigure->setTooltip("This figure represents the radio mode of a radio");
    radioModeFigure->setAssociatedObject(const_cast<cModule *>(module));
    radioModeFigure->setImages(radioModeImages);
    radioModeFigure->setSize(cFigure::Point(width, height));
    auto receptionStateFigure = new IndexedImageFigure("receptionState");
    receptionStateFigure->setTags((std::string("receptionState ") + tags).c_str());
    receptionStateFigure->setTooltip("This figure represents the reception state of a radio");
    receptionStateFigure->setImages(receptionStateImages);
    receptionStateFigure->setSize(cFigure::Point(width, height));
    auto transmissionStateFigure = new IndexedImageFigure("transmissionState");
    transmissionStateFigure->setTags((std::string("transmissionState ") + tags).c_str());
    transmissionStateFigure->setTooltip("This figure represents the transmission state of a radio");
    transmissionStateFigure->setImages(transmissionStateImages);
    transmissionStateFigure->setSize(cFigure::Point(width, height));
    auto antennaLobeFigure = new cPolygonFigure("antenna_lobe");
    antennaLobeFigure->setTags("antennaLobe");
    antennaLobeFigure->setTooltip("This figure represents the antenna lobe of a radio");
    antennaLobeFigure->setZIndex(zIndex);
    antennaLobeFigure->setOutlined(true);
    antennaLobeFigure->setLineColor(antennaLobeLineColor);
    antennaLobeFigure->setLineStyle(antennaLobeLineStyle);
    antennaLobeFigure->setLineWidth(antennaLobeLineWidth);
    antennaLobeFigure->setFilled(true);
    antennaLobeFigure->setFillColor(antennaLobeFillColor);
    antennaLobeFigure->setFillOpacity(antennaLobeOpacity);
    antennaLobeFigure->setSmooth(true);
    auto antenna = radio->getAntenna();
    EulerAngles direction;
    for (deg angle = deg(0); angle != deg(360); angle += antennaLobeStep) {
        if (!strcmp(antennaLobePlane, "view"))
            // TODO:
            direction;
        else if (!strcmp(antennaLobePlane, "xy"))
            direction.alpha = angle;
        else if (!strcmp(antennaLobePlane, "xz"))
            direction.beta = angle;
        else
            throw cRuntimeError("Unknown antennaLobePlane");
        double gain = antenna->getGain()->computeGain(direction);
        cFigure::Point point(antennaLobeRadius * gain * cos(rad(angle).get()), antennaLobeRadius * gain * sin(rad(angle).get()));
        antennaLobeFigure->addPoint(point);
    }
    auto networkNode = getContainingNode(module);
    auto networkNodeVisualization = networkNodeVisualizer->getNetworkNodeVisualization(networkNode);
    return new RadioCanvasVisualization(networkNodeVisualization, radioModeFigure, receptionStateFigure, transmissionStateFigure, antennaLobeFigure, module->getId());
}

void RadioCanvasVisualizer::addRadioVisualization(const RadioVisualization *radioVisualization)
{
    RadioVisualizerBase::addRadioVisualization(radioVisualization);
    auto radioCanvasVisualization = static_cast<const RadioCanvasVisualization *>(radioVisualization);
    radioCanvasVisualization->networkNodeVisualization->addAnnotation(radioCanvasVisualization->radioModeFigure, radioCanvasVisualization->radioModeFigure->getSize(), placementHint, placementPriority);
    radioCanvasVisualization->networkNodeVisualization->addAnnotation(radioCanvasVisualization->receptionStateFigure, radioCanvasVisualization->receptionStateFigure->getSize(), placementHint, placementPriority);
    radioCanvasVisualization->networkNodeVisualization->addAnnotation(radioCanvasVisualization->transmissionStateFigure, radioCanvasVisualization->transmissionStateFigure->getSize(), placementHint, placementPriority);
    radioCanvasVisualization->networkNodeVisualization->addFigure(radioCanvasVisualization->antennaLobeFigure);
}

void RadioCanvasVisualizer::removeRadioVisualization(const RadioVisualization *radioVisualization)
{
    RadioVisualizerBase::removeRadioVisualization(radioVisualization);
    auto radioCanvasVisualization = static_cast<const RadioCanvasVisualization *>(radioVisualization);
    radioCanvasVisualization->networkNodeVisualization->removeAnnotation(radioCanvasVisualization->radioModeFigure);
    radioCanvasVisualization->networkNodeVisualization->removeAnnotation(radioCanvasVisualization->receptionStateFigure);
    radioCanvasVisualization->networkNodeVisualization->removeAnnotation(radioCanvasVisualization->transmissionStateFigure);
    radioCanvasVisualization->networkNodeVisualization->removeFigure(radioCanvasVisualization->antennaLobeFigure);
}

void RadioCanvasVisualizer::refreshRadioVisualization(const RadioVisualization *radioVisualization) const
{
    auto radioCanvasVisualization = static_cast<const RadioCanvasVisualization *>(radioVisualization);
    auto module = getSimulation()->getComponent(radioCanvasVisualization->radioModuleId);
    if (module != nullptr) {
        auto radio = check_and_cast<IRadio *>(module);
        setImageIndex(radioCanvasVisualization->radioModeFigure, radio->getRadioMode());
        setImageIndex(radioCanvasVisualization->receptionStateFigure, radio->getReceptionState());
        setImageIndex(radioCanvasVisualization->transmissionStateFigure, radio->getTransmissionState());
        radioCanvasVisualization->receptionStateFigure->setAssociatedObject(const_cast<cObject *>(dynamic_cast<const cObject *>(radio->getReceptionInProgress())));
        radioCanvasVisualization->transmissionStateFigure->setAssociatedObject(const_cast<cObject *>(dynamic_cast<const cObject *>(radio->getTransmissionInProgress())));
    }
}

void RadioCanvasVisualizer::setImageIndex(IndexedImageFigure *indexedImageFigure, int index) const
{
    indexedImageFigure->setValue(0, simTime(), index);
    indexedImageFigure->setVisible(indexedImageFigure->getImages()[index] != "-");
}

} // namespace visualizer

} // namespace inet

