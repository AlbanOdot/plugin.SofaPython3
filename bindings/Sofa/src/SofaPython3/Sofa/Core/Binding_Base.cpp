
#include <pybind11/pybind11.h>

#include <pybind11/numpy.h>

#include <sofa/core/topology/Topology.h>

#include <sofa/core/objectmodel/BaseData.h>
using sofa::core::objectmodel::BaseData;

#include <sofa/core/objectmodel/BaseLink.h>
using sofa::core::objectmodel::BaseLink;

#include <sofa/helper/Factory.h>
#include <sofa/helper/Factory.inl>

#include <sofa/helper/accessor.h>
using sofa::helper::WriteOnlyAccessor;

#include <SofaPython3/PythonDownCast.h>

#include "Binding_Base.h"
#include "Binding_Base_doc.h"

#include "Binding_BaseData.h"
#include "Binding_DataContainer.h"

#include <sofa/simulation/Node.h>
using sofa::simulation::Node;

#include <sofa/core/objectmodel/BaseObject.h>
using sofa::core::objectmodel::BaseObject;
#include <sofa/core/objectmodel/BaseNode.h>
using sofa::core::objectmodel::BaseNode;
#include <sofa/core/objectmodel/BaseContext.h>
using sofa::core::objectmodel::BaseContext;



namespace sofapython3
{
template<typename DataType>
class DataCreator : public sofa::helper::BaseCreator<sofa::core::objectmodel::BaseData>
{
public:
    virtual sofa::core::objectmodel::BaseData* createInstance(sofa::helper::NoArgument) override { return new sofa::core::objectmodel::Data<DataType>(); }
    virtual const std::type_info& type() override { return typeid(sofa::core::objectmodel::BaseData);}
};

typedef sofa::helper::Factory< std::string, BaseData> DataFactory;

DataFactory* getFactoryInstance(){
    static DataFactory* s_localfactory = nullptr ;
    if (s_localfactory == nullptr)
    {
        // helper vector style containers
        std::string containers[] = {"vector"};

        s_localfactory = new DataFactory();
        // Scalars
        s_localfactory->registerCreator("str", new DataCreator<std::string>());
        s_localfactory->registerCreator("float", new DataCreator<float>());
        s_localfactory->registerCreator("double", new DataCreator<double>());
        s_localfactory->registerCreator("bool", new DataCreator<bool>());
        s_localfactory->registerCreator("int", new DataCreator<int>());

        // vectors
        s_localfactory->registerCreator(
                    "Vec2d", new DataCreator<sofa::defaulttype::Vec2d>());
        s_localfactory->registerCreator(
                    "Vec3d", new DataCreator<sofa::defaulttype::Vec3d>());
        s_localfactory->registerCreator(
                    "Vec4d", new DataCreator<sofa::defaulttype::Vec4d>());
        s_localfactory->registerCreator(
                    "Vec6d", new DataCreator<sofa::defaulttype::Vec6d>());
        s_localfactory->registerCreator(
                    "Vec2f", new DataCreator<sofa::defaulttype::Vec2d>());
        s_localfactory->registerCreator(
                    "Vec3f", new DataCreator<sofa::defaulttype::Vec3d>());
        s_localfactory->registerCreator(
                    "Vec4f", new DataCreator<sofa::defaulttype::Vec4d>());
        s_localfactory->registerCreator(
                    "Vec6f", new DataCreator<sofa::defaulttype::Vec6d>());

        // Matrices
        s_localfactory->registerCreator(
                    "Mat2x2d", new DataCreator<sofa::defaulttype::Mat2x2d>());
        s_localfactory->registerCreator(
                    "Mat3x3d", new DataCreator<sofa::defaulttype::Mat3x3d>());
        s_localfactory->registerCreator(
                    "Mat4x4d", new DataCreator<sofa::defaulttype::Mat4x4d>());
        s_localfactory->registerCreator(
                    "Mat2x2f", new DataCreator<sofa::defaulttype::Mat2x2f>());
        s_localfactory->registerCreator(
                    "Mat3x3f", new DataCreator<sofa::defaulttype::Mat3x3f>());
        s_localfactory->registerCreator(
                    "Mat4x4f", new DataCreator<sofa::defaulttype::Mat4x4f>());

        // Topology
        s_localfactory->registerCreator("Edge", new DataCreator<sofa::core::topology::Topology::Edge>());
        s_localfactory->registerCreator("Triangle", new DataCreator<sofa::core::topology::Topology::Triangle>());
        s_localfactory->registerCreator("Quad", new DataCreator<sofa::core::topology::Topology::Quad>());
        s_localfactory->registerCreator("Tetra", new DataCreator<sofa::core::topology::Topology::Tetra>());
        s_localfactory->registerCreator("Hexa", new DataCreator<sofa::core::topology::Topology::Hexa>());
        s_localfactory->registerCreator("Penta", new DataCreator<sofa::core::topology::Topology::Penta>());

        // State vectors
        s_localfactory->registerCreator(
                    "Rigid3d::VecCoord", new DataCreator<sofa::defaulttype::Rigid3dTypes::VecCoord>());
        s_localfactory->registerCreator(
                    "Rigid3f::VecCoord", new DataCreator<sofa::defaulttype::Rigid3fTypes::VecCoord>());
        s_localfactory->registerCreator(
                    "Rigid3::VecCoord", new DataCreator<sofa::defaulttype::Rigid3Types::VecCoord>());

        // General vectors
        for (const auto& container : containers)
        {
            // Scalars
            s_localfactory->registerCreator(container + "<string>",
                                            new DataCreator<sofa::helper::vector<std::string>>());
            s_localfactory->registerCreator(container + "<float>",
                                            new DataCreator<sofa::helper::vector<float>>());
            s_localfactory->registerCreator(container + "<double>",
                                            new DataCreator<sofa::helper::vector<double>>());
            s_localfactory->registerCreator(container + "<bool>",
                                            new DataCreator<sofa::helper::vector<bool>>());
            s_localfactory->registerCreator(container + "<int>",
                                            new DataCreator<sofa::helper::vector<int>>());

            // vectors
            s_localfactory->registerCreator(
                        container + "<Vec2d>", new DataCreator<sofa::helper::vector<sofa::defaulttype::Vec2d>>());
            s_localfactory->registerCreator(
                        container + "<Vec3d>", new DataCreator<sofa::helper::vector<sofa::defaulttype::Vec3d>>());
            s_localfactory->registerCreator(
                        container + "<Vec4d>", new DataCreator<sofa::helper::vector<sofa::defaulttype::Vec4d>>());
            s_localfactory->registerCreator(
                        container + "<Vec6d>", new DataCreator<sofa::helper::vector<sofa::defaulttype::Vec6d>>());
            s_localfactory->registerCreator(
                        container + "<Vec2f>", new DataCreator<sofa::helper::vector<sofa::defaulttype::Vec2f>>());
            s_localfactory->registerCreator(
                        container + "<Vec3f>", new DataCreator<sofa::helper::vector<sofa::defaulttype::Vec3f>>());
            s_localfactory->registerCreator(
                        container + "<Vec4f>", new DataCreator<sofa::helper::vector<sofa::defaulttype::Vec4f>>());
            s_localfactory->registerCreator(
                        container + "<Vec6f>", new DataCreator<sofa::helper::vector<sofa::defaulttype::Vec6f>>());

            // Matrices
            s_localfactory->registerCreator(
                        container + "<Mat2x2d>",
                        new DataCreator<sofa::helper::vector<sofa::defaulttype::Mat2x2d>>());
            s_localfactory->registerCreator(
                        container + "<Mat3x3d>",
                        new DataCreator<sofa::helper::vector<sofa::defaulttype::Mat3x3d>>());
            s_localfactory->registerCreator(
                        container + "<Mat4x4d>",
                        new DataCreator<sofa::helper::vector<sofa::defaulttype::Mat4x4d>>());
            s_localfactory->registerCreator(
                        container + "<Mat2x2f>",
                        new DataCreator<sofa::helper::vector<sofa::defaulttype::Mat2x2f>>());
            s_localfactory->registerCreator(
                        container + "<Mat3x3f>",
                        new DataCreator<sofa::helper::vector<sofa::defaulttype::Mat3x3f>>());
            s_localfactory->registerCreator(
                        container + "<Mat4x4f>",
                        new DataCreator<sofa::helper::vector<sofa::defaulttype::Mat4x4f>>());

            // Topology
            s_localfactory->registerCreator(container + "<Edge>",
                                            new DataCreator<sofa::helper::vector<sofa::core::topology::Topology::Edge>>());
            s_localfactory->registerCreator(container + "<Triangle>",
                                            new DataCreator<sofa::helper::vector<sofa::core::topology::Topology::Triangle>>());
            s_localfactory->registerCreator(container + "<Quad>",
                                            new DataCreator<sofa::helper::vector<sofa::core::topology::Topology::Quad>>());
            s_localfactory->registerCreator(container + "<Tetra>",
                                            new DataCreator<sofa::helper::vector<sofa::core::topology::Topology::Tetra>>());
            s_localfactory->registerCreator(container + "<Hexa>",
                                            new DataCreator<sofa::helper::vector<sofa::core::topology::Topology::Hexa>>());
            s_localfactory->registerCreator(container + "<Penta>",
                                            new DataCreator<sofa::helper::vector<sofa::core::topology::Topology::Penta>>());
        }
    }
    return s_localfactory ;
}

///@brief return a py::object for the provided name 's'.
///
/// It is possible to control if the function is throwing an exception when
/// the provided name is not found in the 'self' object.
py::object BindingBase::GetAttr(Base* self, const std::string& s, bool doThrowException)
{
    /// I'm not sure implicit behavior is nice but we could do:
    ///    - The attribute is a data,
    ///         returns it if it is a container
    ///         returns the value/specific binding otherwise
    ///    - The attribute is a link, return it.
    ///    - The attribute is an object or a child return it.
    ///    - The attribute is not existing:
    ///                raise an exception or search using difflib for close match.
    if(self==nullptr)
        throw py::attribute_error("Cannot get a Sofa attribute from None.");

    /// We are selecting first into data, then into link. Because
    /// this seems to be the most common use-case.

    /// Search if there is a data with the given name.
    /// If this is the case returns the corresponding python type.
    if(BaseData* d = self->findData(s)){
        return dataToPython(d);
    }

    /// Search if there is a link with the given name.
    /// If this is the case returns the corresponding python type.
    if(BaseLink* l = self->findLink(s))
        return py::cast(l->getLinkedBase());

    /// Search if we are quering for a 'magic' and private __data__ property
    /// this one allows to traverse all the data in the object
    if( s == "__data__")
        return py::cast( DataDict(self) );

    if(doThrowException)
        throw py::attribute_error("Missing attribute: "+s);

    return py::none();
}

bool BindingBase::SetData(BaseData* d, py::object value)
{
    if(d==nullptr)
        return false;

    const AbstractTypeInfo& nfo{ *(d->getValueTypeInfo()) };

    /// We go for the container path.
    if(nfo.Container())
    {
        fromPython(d,value);
        return true;
    }
    fromPython(d, value);
    return true;
}


void BindingBase::SetAttr(py::object self, const std::string& s, py::object value)
{
    Base* self_d = py::cast<Base*>(self);
    BaseData* d = self_d->findData(s);

    if(d!=nullptr)
    {
        SetData(d, value);
        return;
    }

    BaseLink* l = self_d->findLink(s);
    if(l!=nullptr)
    {
        return;
    }

    /// We are falling back to dynamically adding the objet into the object dict.
    py::dict t = self.attr("__dict__");
    if(!t.is_none())
    {
        t[s.c_str()] = value;
        return;
    }

    /// Well this should never happen unless there is no __dict__
    throw py::attribute_error("Unable to set attribute '"+s+"', unknow data type");
}

void BindingBase::SetAttr(Base& self, const std::string& s, py::object value)
{
    BaseData* d = self.findData(s);

    if(d!=nullptr)
    {
        const AbstractTypeInfo& nfo{ *(d->getValueTypeInfo()) };

        /// We go for the container path.
        if(nfo.Container())
        {
            fromPython(d,value);
            return;
        }
        fromPython(d, value);
        return;
    }

    BaseLink* l = self.findLink(s);
    if(l!=nullptr)
    {
        return;
    }

    throw py::attribute_error(self.name.getValue() + " has no data field nor link named '" + s + "'");
}

void BindingBase::SetDataFromArray(BaseData* data, const py::array& value)
{
    if(data==nullptr)
        return;

    const AbstractTypeInfo& nfo{ *(data->getValueTypeInfo()) };

    /// We go for the container path.
    if(nfo.Container())
    {
        py::array dst = getPythonArrayFor(data);
        py::buffer_info dstinfo = dst.request();

        py::array src = value;
        py::buffer_info srcinfo = src.request();
        if( srcinfo.ptr == dstinfo.ptr )
        {
            /// Increment the change counter so other data field can keep track of
            /// what happens.
            data->beginEditVoidPtr();
            data->endEditVoidPtr();
            return;
        }

        /// Invalid dimmensions
        if( srcinfo.ndim != dst.ndim() )
            throw py::type_error("Invalid dimension");

        bool needResize = false;
        size_t resizeShape=0;
        size_t srcSize = 1;
        for(auto i=0;i<srcinfo.ndim;++i){
            srcSize *= srcinfo.shape[i];
            if( srcinfo.shape[i] != dstinfo.shape[i])
            {
                resizeShape = i;
                needResize = true;
            }
        }

        if(needResize)
        {
            if(nfo.FixedSize())
                throw py::index_error("The destination is not large enough and cannot be resized. Please clamp the source data set before setting.");

            if(resizeShape != 0)
                throw py::index_error("The destination can only be resized on the first dimension. ");

            /// Change the allocated memory of the data field, then update the
            /// cache entry so keep up with the changes. As we use dstinfo in the following
            /// we also update it.
            nfo.setSize(data->beginEditVoidPtr(), srcSize);
            dst = resetArrayFor(data);
            dstinfo=dst.request();
        }

        bool sameDataType = (srcinfo.format == dstinfo.format);
        if(sameDataType && (nfo.BaseType()->FixedSize() || nfo.SimpleCopy()))
        {
            scoped_writeonly_access guard(data);
            memcpy(dstinfo.ptr, srcinfo.ptr, srcSize*dstinfo.itemsize);
            return;
        }

        /// In this case we go for the fast path.
        if(nfo.SimpleLayout())
        {
            if(srcinfo.format=="d")
                return copyScalar<double>(data, nfo, src);
            else if(srcinfo.format=="f")
                return copyScalar<float>(data, nfo, src);
            else
                std::cout << "SetAttrFromArray :: unsupported fileformat" << std::endl ;
        }

    }

    fromPython(data, value);
    return;
}

void BindingBase::SetAttrFromArray(py::object self, const std::string& s, const py::array& value)
{
    /// I'm not sure implicit behavior is nice but we could do:
    ///    - The attribute is a data, set its value.
    ///          If the data is a container...check dimmensions and do type coercion.
    ///    - The attribute is a link, set its value.
    ///    - The attribute is an object or a child, raise an exception.
    ///    - The attribute is not existing, add it has data with type deduced from value ?
    Base& self_base = py::cast<Base&>(self);
    BaseData* data = self_base.findData(s);

    /// If there is a data with the given name we set the data value.
    if(data!=nullptr)
    {
        SetDataFromArray(data, value);
        return;
    }

    /// We are falling back to dynamically adding the objet into the object dict.
    py::dict t = self.attr("__dict__");
    if(!t.is_none())
    {
        t[s.c_str()] = value;
        return;
    }

    /// Well this should never happen unless there is no __dict__
    throw py::attribute_error("");
}

void moduleAddDataDict(py::module& m)
{
    ////////////////////////////////////////////////////////////////////////////////////////////////
    /// DataDict binding
    ////////////////////////////////////////////////////////////////////////////////////////////////
    py::class_<DataDict> d(m, "DataDict",
                           sofapython3::doc::dataDict::Class);
    d.def("__len__", [](DataDict& self)
    {
        return self.owner->getDataFields().size();
    });


    d.def("__getitem__",[](DataDict& self, const size_t& i)
    {
        const Base::VecData& vd = self.owner->getDataFields();
        if(i > vd.size())
            throw py::index_error(std::to_string(i));
        return toPython(vd[i]);
    });

    d.def("__getitem__",
          [](DataDict& self, const std::string& s) -> py::object
    {
        BaseData* d = self.owner->findData(s);
        if(d!=nullptr)
        {
            const AbstractTypeInfo& nfo{ *(d->getValueTypeInfo()) };

            if(nfo.Container())
            {
                py::array a = py::array(toBufferInfo(*d));
                return a;
            }
            if(nfo.Text()) {
                //                return py::cast(reinterpret_cast<DataAsString*>(d));
                return py::cast(d->getValueString());
            }
            return py::cast(d);
        }
        throw std::invalid_argument(s);
    });

    ////////////////////////////////////////////////////////////////////////////////////////////////
    d.def("__setitem__",[](DataDict& d, const std::string& s, py::object v)
    {
        return 0.0;
    });

    d.def("__iter__", [](DataDict& d)
    {
        return DataDictIterator(d.owner, true, false);
    });
    d.def("keys", [](DataDict& d)
    {
        return DataDictIterator(d.owner, true, false);
    }, sofapython3::doc::dataDict::keys);
    d.def("values", [](DataDict& d)
    {
        return DataDictIterator(d.owner, false, true);
    }, sofapython3::doc::dataDict::values);
    d.def("items", [](DataDict& d)
    {
        return DataDictIterator(d.owner, true, true);
    }, sofapython3::doc::dataDict::items);
}


void moduleAddDataDictIterator(py::module &m)
{
    PythonDownCast::registerType<sofa::core::objectmodel::Base>(
                [](sofa::core::objectmodel::Base* object)
    {
        return py::cast(object);
    });


    py::class_<DataDictIterator> ddi(m, "DataDictIterator");
    ddi.def("__iter__", [](DataDictIterator& d)
    {
        return d;
    });
    ddi.def("__next__", [](DataDictIterator& d) -> py::object
    {
        if(d.index>=d.owner->getDataFields().size())
            throw py::stop_iteration();

        BaseData* data = d.owner->getDataFields()[d.index++];
        if(!d.key)
            return toPython(data);

        if(!d.value)
            return py::cast(data->getName());

        py::tuple t {2};
        t[0] = data->getName();
        t[1] = toPython(data);
        return std::move(t);
    });
}

BaseData* deriveTypeFromParent(BaseData* parentData)
{
    BaseData* newData = parentData->getNewInstance();
    newData->setParent(parentData);
    newData->update();
    return newData;
}

BaseData* deriveTypeFromParent(BaseContext* ctx, const std::string& link)
{
    std::cout << "link is : " << link << std::endl;
    if (!ctx)
        return nullptr;

    std::cout << "ctx is : " << ctx->toBaseNode()->getPathName() << std::endl;
    // if data is a link
    if (link.empty() || link[0] != '@')
        return nullptr;

    std::string componentPath = link.substr(0, link.find('.'));
    std::string parentDataName = link.substr(link.find('.') + 1);
    std::cout << "ComponentPath is: " << componentPath << std::endl;
    std::cout << "parentDataName is: " << parentDataName << std::endl;

    std::list<std::string> token_list;
    std::istringstream iss(componentPath);
    std::copy(std::istream_iterator<std::string>(iss),
         std::istream_iterator<std::string>(),
         std::back_inserter(token_list));


    Base* component = ctx->toBaseNode();
    std::cout << component->getName() << std::endl;
    for (auto& name : token_list)
    {
        if (name == "@")
            continue;

        component = component->toBaseContext()->get<Base>(name);
        if (!component)
        {
            throw py::value_error("SofaPython: No object or node with path " + componentPath + " in scene graph.");
        }
        std::cout << component->getName() << std::endl;
    }

    BaseData* parentData = component->findData(parentDataName);
    std::cout << parentData->getName() << std::endl;
    return deriveTypeFromParent(parentData);
}

bool isProtectedKeyword(const std::string& name)
{
    if (name == "children" || name == "objects" || name == "parents" ||
            name == "data" || name == "links")
    {
        return true;
    }
    return false;
}

void checkAmbiguousCreation(BaseNode* self, const std::string& name, const std::string& type)
{
    if (!self) return;

    if (type != "link")
        for (const auto& link : self->getLinks())
            if (link->getName() == name)
                msg_warning(self) << "Ambiguous creation of " << type << " named '" << name << "' in " << self->getPathName() << ": Component alread has a link with such name";

    if (type != "data")
        for (const auto& datafield : self->getDataFields())
            if (datafield->getName() == name)
                msg_warning(self) << "Ambiguous creation of " << type << " named '" << name << "' in " << self->getPathName() << ": Component alread has a data field with such name";

    if (type != "object")
        for (const auto& o : dynamic_cast<Node*>(self)->object)
            if (o->getName() == name)
                msg_warning(self) << "Ambiguous creation of " << type << " named '" << name << "' in " << self->getPathName() << ": Component alread has an object with such name";

    if (type != "child")
        for (const auto& child : self->getChildren())
            if (child->getName() == name)
                msg_warning(self) << "Ambiguous creation of " << type << " named '" << name << "' in " << self->getPathName() << ": Component alread has a child node with such name";

}

void checkAmbiguousCreation(BaseObject* self, const std::string& name, const std::string& type)
{
    if (!self) return;

    if (type != "link")
        for (const auto& link : self->getLinks())
            if (link->getName() == name)
                msg_warning(self) << "Ambiguous creation of " << type << " named '" << name << "' in " << self->getPathName() << ": Component alread has a link with such name";

    if (type != "data")
        for (const auto& datafield : self->getDataFields())
            if (datafield->getName() == name)
                msg_warning(self) << "Ambiguous creation of " << type << " named '" << name << "' in " << self->getPathName() << ": Component alread has a data field with such name";
}

void checkAmbiguousCreation(Base* self, const std::string& name, const std::string& type)
{
    checkAmbiguousCreation(dynamic_cast<BaseNode*>(self), name, type);
    checkAmbiguousCreation(dynamic_cast<BaseObject*>(self), name, type);
}

void checkAmbiguousCreation(py::object& py_self, const std::string& name, const std::string& type)
{
    Base* self = py::cast<Base*>(py_self);
    checkAmbiguousCreation(dynamic_cast<BaseNode*>(self), name, type);
    checkAmbiguousCreation(dynamic_cast<BaseObject*>(self), name, type);

    if (py_self.attr("__dict__").contains(name))
        msg_warning(self) << "Ambiguous creation of " << type << " named '" << name << "' in " << self->getName() << ": Component alread has a python attribute with such name in __dict__";
}

void _addData(Base* self, BaseData* data, const std::string& name)
{
    if (data->getOwner() == nullptr)
        self->addData(data, name);
    else
    {
        BaseData* newData = data->getNewInstance();
        newData->setOwner(self);
        newData->setParent(data);
        newData->setName(name);
        self->addData(newData);
        newData->update();
    }
}

void moduleAddBase(py::module &m)
{
    py::class_<Base, Base::SPtr> base(m, "Base", py::dynamic_attr(), doc::base::BaseClass);

    base.def("getName", &Base::getName,
             pybind11::return_value_policy::copy,
             doc::base::getName, sofapython3::doc::base::getName);
    base.def("setName", pybind11::overload_cast<const std::string&>(&Base::setName), sofapython3::doc::base::setName);
    base.def("setName", pybind11::overload_cast<const std::string&, int>(&Base::setName), sofapython3::doc::base::setNameCounter);
    base.def("getClass", &Base::getClass, pybind11::return_value_policy::reference, sofapython3::doc::base::getClass);
    base.def("getDefinitionSourceFilePos", &Base::getDefinitionSourceFilePos,
             sofapython3::doc::base::getDefinitionSourceFilePos);
    base.def("getDefinitionSourceFileName", &Base::getDefinitionSourceFileName,
             sofapython3::doc::base::getDefinitionSourceFileName);
    base.def("getInstanciationSourceFilePos", &Base::getInstanciationSourceFilePos,
             sofapython3::doc::base::getInstanciationSourceFilePos);
    base.def("getInstanciationFileName", &Base::getInstanciationSourceFileName,
             sofapython3::doc::base::getInstanciationSourceFilePos);
    base.def("findData", &Base::findData, pybind11::return_value_policy::reference, sofapython3::doc::base::findData);
    base.def("getDataFields", &Base::getDataFields, pybind11::return_value_policy::reference, sofapython3::doc::base::getDataFields);
    base.def("findLink", &Base::findLink, pybind11::return_value_policy::reference, sofapython3::doc::base::findLink);
    base.def("getLinks", &Base::getLinks, pybind11::return_value_policy::reference, sofapython3::doc::base::getLinks);
    base.def("addData", [](py::object py_self, const std::string& name,
             py::object value = py::none(), py::object defaultValue = py::none(), const std::string& help = "",
             const std::string& group = "", std::string type = "")
    {
        bool isDefault = false;
        Base* self = py::cast<Base*>(py_self);
        if (isProtectedKeyword(name))
            throw py::value_error("addData: Cannot call addData with name " + name + ": Protected keyword");
        checkAmbiguousCreation(py_self, name, "data");
        BaseData* data;

        if (py::isinstance<BaseData>(value))
        {
            type = "";
        }

        if (value.is(py::none()))
        {
            std::cout << "value is none. defaulting to whatever u've set as a default" << std::endl;
            if (py::isinstance<BaseData>(defaultValue))
            {
                type = "";
            }
            value = defaultValue;
            isDefault = true;
        }
        // create the data from another data (use as parent)
        if (py::isinstance<BaseData>(value))
        {
            data = deriveTypeFromParent(py::cast<BaseData*>(value));
            if (!data)
                throw py::type_error("Cannot deduce type from value");
            self->addData(data, name);
        }
        // create the data from the link passed as a string to the object
        else if (type.empty() && py::isinstance<py::str>(value))
        {
            if (dynamic_cast<BaseNode*>(self))
                data = deriveTypeFromParent(dynamic_cast<BaseNode*>(self)->getContext(),
                                            py::cast<py::str>(value));
            else
                data = deriveTypeFromParent(dynamic_cast<BaseObject*>(self)->getContext(),
                                            py::cast<py::str>(value));
            if (!data)
                throw py::type_error("Cannot deduce type from value");
            _addData(self, data, name);
        }
        // create the data from the type given in `type` and fill it up
        else
        {
            data = getFactoryInstance()->createObject(type, sofa::helper::NoArgument());
            if (!data)
            {
                sofa::helper::vector<std::string> validTypes;
                getFactoryInstance()->uniqueKeys(std::back_inserter(validTypes));
                std::string typesString = "[";
                for (const auto& i : validTypes)
                    typesString += i + ", ";
                typesString += "\b\b]";

                throw py::type_error(std::string("Invalid Type string: available types are\n") + typesString);
            }
            _addData(self, data, name);
            if (!value.is(py::none()))
            {
                std::cout << "getting python value in data" << std::endl;
                fromPython(data, value);
            }
        }
        data->setName(name);
        data->setGroup(group.c_str());
        data->setHelp(help.c_str());
        data->setDisplayed(true);
        data->setPersistent(true);
        if (isDefault)
            data->unset();
    }, "name"_a, "value"_a = "", "default"_a = "", "help"_a = "", "group"_a = "", "type"_a = "", sofapython3::doc::base::addData);

    base.def("addData", [](Base* self, py::object d) {
        BaseData* data = py::cast<BaseData*>(d);
        if (!data)
            throw py::type_error("Argument is not a Data!");

        _addData(self, data, data->getName());
    }, sofapython3::doc::base::addDataInitialized);

    base.def("addData", [](Base* self, const std::string& name, py::object d) {
        BaseData* data = py::cast<BaseData*>(d);
        if (!data)
            throw py::type_error("Argument is not a Data!");

        _addData(self, data, name);
    }, sofapython3::doc::base::addDataInitialized);

    base.def("__dir__", [](Base* self)
    {
        py::list list;
        for(auto i : self->getDataFields())
        {
            list.append(i->getName());
        }
        return list;
    });

    base.def("getData", [](Base& self, const std::string& s) -> py::object
    {
        BaseData* d = self.findData(s);
        if(d!=nullptr)
        {
            return py::cast(d);
        }
        return py::none();
    }, sofapython3::doc::base::getData);


    base.def("__getattr__", [](py::object self, const std::string& s) -> py::object
    {
        py::object res = BindingBase::GetAttr( py::cast<Base*>(self), s, false );
        if( res.is_none() )
        {
            return self.attr("__dict__")[s.c_str()];
        }

        return res;
    });

    base.def("__setattr__", [](py::object self, const std::string& s, py::object value)
    {
        if(py::isinstance<DataContainer>(value))
        {
            BaseData* data = py::cast<BaseData*>(value);
            py::array a = getPythonArrayFor(data);
            BindingBase::SetAttrFromArray(self,s, a);
            return;
        }

        if(py::isinstance<py::array>(value))
        {
            BindingBase::SetAttrFromArray(self,s, py::cast<py::array>(value));
            return;
        }

        BindingBase::SetAttr(self,s,value);
    });
    base.def("getClassName",&Base::getClassName, sofapython3::doc::base::getClassName);
    base.def("getTemplateName",&Base::getTemplateName, sofapython3::doc::base::getTemplateName);
}

} /// namespace sofapython3
