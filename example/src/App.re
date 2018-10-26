open BsCountrySelect;

type state = {selectedCountry: option(string)};

type action =
  | ChangeSelectedCountry(option(string));

let component = ReasonReact.reducerComponent(__MODULE__);

let make = _children => {
  ...component,
  initialState: () => {selectedCountry: None},
  reducer: (action, state: state) =>
    switch (action) {
    | ChangeSelectedCountry(Some(value)) => ReasonReact.Update({ selectedCountry: Some(value) })
    | ChangeSelectedCountry(None) => ReasonReact.Update({ selectedCountry: None})
    },
  render: self =>
    <div>
      <h2> (ReasonReact.string("LAL a Country")) </h2>
      <CountrySelect
        className="custom-class"
        country=?self.state.selectedCountry
        onChange=(
          country => self.send(ChangeSelectedCountry(country->Belt.Option.map(c => c##value)))
        )
      />
    </div>,
};
