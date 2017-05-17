#ifndef UIFUNCTIONS_H_INCLUDED
#define UIFUNCTIONS_H_INCLUDED

#include <QObject>
#include <QString>

#include "Proxy.h"
#include "stubs.h"
#include "widgets/all.h"

class UIFunctions : public QObject
{
    Q_OBJECT

public:
    virtual ~UIFunctions();

    static UIFunctions * getInstance(QObject *parent = 0);
    static void destroyInstance();

    void connectSignals();

private:
    UIFunctions(QObject *parent = 0);

    static UIFunctions *instance;

public slots:

private slots:
    void onButtonClick(Widget *widget);
    void onLinkActivated(Widget *widget, QString link);
    void onValueChangeInt(Widget *widget, int value);
    void onValueChangeDouble(Widget *widget, double value);
    void onValueChangeString(Widget *widget, QString value);
    void onEditingFinished(Edit *edit, QString value);
    void onWindowClose(Window *window);
    void onLoadImageFromFile(Image *image, const char *filename, int w, int h);
    void onPlottableClick(Plot *plot, std::string name, int index, double x, double y);
    void onLegendClick(Plot *plot, std::string name);
    void onCellActivate(Table *table, int row, int col, std::string text);
    void onSelectionChangeTable(Table *table, int row, int col);
    void onSelectionChangeTree(Tree *tree, int id);
    void onMouseEvent(Image *image, int type, bool shift, bool control, int x, int y);
    void onNodeAdded(Dataflow *dataflow, int id, QPoint pos, QString text, int inlets, int outlets);
    void onNodeRemoved(Dataflow *dataflow, int id);
    void onNodeValidChanged(Dataflow *dataflow, int id, bool valid);
    void onNodePosChanged(Dataflow *dataflow, int id, QPoint pos);
    void onNodeTextChanged(Dataflow *dataflow, int id, QString text);
    void onNodeInletCountChanged(Dataflow *dataflow, int id, int inlets);
    void onNodeOutletCountChanged(Dataflow *dataflow, int id, int outlets);
    void onConnectionAdded(Dataflow *dataflow, int srcNodeId, int srcOutlet, int dstNodeId, int dstInlet);
    void onConnectionRemoved(Dataflow *dataflow, int srcNodeId, int srcOutlet, int dstNodeId, int dstInlet);
    void onKeyPress(Widget *widget, int key, std::string text);

signals:
    void create(Proxy *proxy);
    void destroy(Proxy *proxy);
    void showWindow(Window *window);
    void hideWindow(Window *window);
    void setPosition(Window *window, int x, int y);
    void setSize(Window *window, int w, int h);
    void setTitle(Window *window, std::string title);
    void setImage(Image *image, const char *data, int w, int h);
    void sceneChange(Window *window, int oldSceneID, int newSceneID);
    void setEnabled(Widget *widget, bool enabled);
    void setEditValue(Edit *edit, std::string value, bool suppressSignals);
    void setSpinboxValue(Spinbox *spinbox, double value, bool suppressSignals);
    void setLabelText(Label *label, std::string text, bool suppressSignals);
    void setSliderValue(Slider *slider, int value, bool suppressSignals);
    void setCheckboxValue(Checkbox *checkbox, Qt::CheckState value, bool suppressSignals);
    void setRadiobuttonValue(Radiobutton *radiobutton, bool value, bool suppressSignals);
    void insertComboboxItem(Combobox *combobox, int index, std::string text, bool suppressSignals);
    void removeComboboxItem(Combobox *combobox, int index, bool suppressSignals);
    void setComboboxItems(Combobox *combobox, std::vector<std::string> items, int index, bool suppressEvents);
    void setComboboxSelectedIndex(Combobox *combobox, int index, bool suppressEvents);
    void setCurrentTab(Tabs *tabs, int index, bool suppressSignals);
    void setWidgetVisibility(Widget *widget, bool visible);
    void replot(Plot *plot);
    void addCurve(Plot *plot, int type, std::string name, std::vector<int> color, int style, curve_options *opts);
    void addCurveTimePoints(Plot *plot, std::string name, std::vector<double> x, std::vector<double> y);
    void addCurveXYPoints(Plot *plot, std::string name, std::vector<double> t, std::vector<double> x, std::vector<double> y);
    void clearCurve(Plot *plot, std::string name);
    void removeCurve(Plot *plot, std::string name);
    void setPlotRanges(Plot *plot, double xmin, double xmax, double ymin, double ymax);
    void setPlotXRange(Plot *plot, double xmin, double xmax);
    void setPlotYRange(Plot *plot, double ymin, double ymax);
    void growPlotRanges(Plot *plot, double xmin, double xmax, double ymin, double ymax);
    void growPlotXRange(Plot *plot, double xmin, double xmax);
    void growPlotYRange(Plot *plot, double ymin, double ymax);
    void setPlotLabels(Plot *plot, std::string x, std::string y);
    void setPlotXLabel(Plot *plot, std::string label);
    void setPlotYLabel(Plot *plot, std::string label);
    void rescaleAxes(Plot *plot, std::string name, bool onlyEnlargeX, bool onlyEnlargeY);
    void rescaleAxesAll(Plot *plot, bool onlyEnlargeX, bool onlyEnlargeY);
    void setMouseOptions(Plot *plot, bool panX, bool panY, bool zoomX, bool zoomY);
    void setLegendVisibility(Plot *plot, bool visible);
    void clearTable(Table *table);
    void setRowCount(Table *table, int count);
    void setColumnCountTable(Table *table, int count);
    void setItem(Table *table, int row, int col, std::string text);
    void setRowHeaderText(Table *table, int row, std::string text);
    void setColumnHeaderTextTable(Table *table, int col, std::string text);
    void setItemEditable(Table *table, int row, int col, bool editable);
    void restoreStateTable(Table *table, std::string state);
    void setRowHeight(Table *table, int row, int min_size, int max_size);
    void setColumnWidthTable(Table *table, int column, int min_size, int max_size);
    void setTableSelection(Table *table, int row, int col);
    void setProgress(Progressbar *progressbar, int value);
    void setColumnCountTree(Tree *tree, int count);
    void setColumnHeaderTextTree(Tree *tree, int col, std::string text);
    void restoreStateTree(Tree *tree, std::string state);
    void setColumnWidthTree(Tree *tree, int column, int min_size, int max_size);
    void clearTree(Tree *tree);
    void addTreeItem(Tree *tree, int item_id, int parent_id, std::vector<std::string> text, bool expanded);
    void updateTreeItemText(Tree *tree, int item_id, std::vector<std::string> text);
    void updateTreeItemParent(Tree *tree, int item_id, int parent_id);
    void removeTreeItem(Tree *tree, int item_id);
    void setTreeSelection(Tree *tree, int item_id);
    void expandAll(Tree *tree);
    void collapseAll(Tree *tree);
    void expandToDepth(Tree *tree, int depth);
    void addNode(Dataflow *dataflow, int id, QPoint pos, QString text, int inlets, int outlets);
    void removeNode(Dataflow *dataflow, int id);
    void setNodeValid(Dataflow *dataflow, int id, bool valid);
    void setNodePos(Dataflow *dataflow, int id, QPoint pos);
    void setNodeText(Dataflow *dataflow, int id, QString text);
    void setNodeInletCount(Dataflow *dataflow, int id, int count);
    void setNodeOutletCount(Dataflow *dataflow, int id, int count);
    void addConnection(Dataflow *dataflow, int srcId, int srcOutlet, int dstId, int dstInlet);
    void removeConnection(Dataflow *dataflow, int srcId, int srcOutlet, int dstId, int dstInlet);
    void setText(TextBrowser *textbrowser, std::string text, bool suppressSignals);
    void setUrl(TextBrowser *textbrowser, std::string url);
};

#endif // UIFUNCTIONS_H_INCLUDED

